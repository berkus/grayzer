#![feature(box_syntax)]
#![feature(clamp)]

mod environment;
mod geom;
mod ray;
mod texture;
mod vec3;

use crate::texture::dielectric::Dielectric;
use crate::texture::metal::Metal;
use environment::{Camera, Scene};
use geom::Sphere;
use rand::Rng;
use ray::Ray;
use std::rc::Rc;
use texture::lambertian::Lambertian;
use vec3::Vec3;

const SAMPLES_PER_PIXEL: u32 = 10;
const MAX_DEPTH: i32 = 50;
const EPSILON: f32 = std::f32::EPSILON;

fn make_scene() -> Scene {
    let mut scene = Scene::new();

    scene.add_solid(box Sphere::new(
        Vec3::new(0.0, -1000.0, -1.0),
        1000.0,
        Rc::new(Lambertian::new(Vec3::new(0.5, 0.5, 0.5))),
    ));

    for a in -11..11 {
        for b in -11..11 {
            let chosen_material: f32 = rand::thread_rng().gen();
            let center = Vec3::new(
                a as f32 + 0.9 * rand::thread_rng().gen::<f32>(),
                0.2,
                b as f32 + 0.9 * rand::thread_rng().gen::<f32>(),
            );
            if (center - Vec3::new(4.0, 0.2, 0.0)).length() > 0.9 {
                match chosen_material {
                    x if x < 0.8 => {
                        // Diffuse
                        let albedo = Vec3::random() * Vec3::random();
                        scene.add_solid(box Sphere::new(
                            center,
                            0.2,
                            Rc::new(Lambertian::new(albedo)),
                        ));
                    }
                    y if y < 0.95 => {
                        // Metal
                        let albedo = Vec3::random_between(0.5, 1.0);
                        let fuzz: f32 = rand::thread_rng().gen_range(0.0, 0.5);
                        scene.add_solid(box Sphere::new(
                            center,
                            0.2,
                            Rc::new(Metal::new(albedo, fuzz)),
                        ));
                    }
                    _ => {
                        let refraction_index: f32 = rand::thread_rng().gen_range(1.3, 2.0);
                        // Glass
                        scene.add_solid(box Sphere::new(
                            center,
                            0.2,
                            Rc::new(Dielectric::new(refraction_index)),
                        ));
                    }
                }
            }
        }
    }

    scene.add_solid(box Sphere::new(
        Vec3::new(0.0, 1.0, 0.0),
        1.0,
        Rc::new(Dielectric::new(1.5)),
    ));

    scene.add_solid(box Sphere::new(
        Vec3::new(-4.0, 1.0, 0.0),
        1.0,
        Rc::new(Lambertian::new(Vec3::new(0.4, 0.2, 0.1))),
    ));

    scene.add_solid(box Sphere::new(
        Vec3::new(4.0, 1.0, 0.0),
        1.0,
        Rc::new(Metal::new(Vec3::new(0.7, 0.6, 0.5), 0.0)),
    ));

    scene
}

fn render_ppm(w: i32, h: i32, max_value: i32) {
    println!("P3\n{} {}\n{}", w, h, max_value);

    let aspect_ratio = w as f32 / h as f32;
    let look_from = Vec3::new(13.0, 2.0, 3.0);
    let look_at = Vec3::new(0.0, 0.0, 0.0);
    let view_up = Vec3::new(0.0, 1.0, 0.0);
    let dist_to_focus = 10.0;
    let aperture = 0.1;
    let camera = Camera::new_free(
        look_from,
        look_at,
        view_up,
        20.0,
        aspect_ratio,
        aperture,
        dist_to_focus,
    );

    let scene = make_scene();

    for y in (0..h).rev() {
        for x in 0..w {
            let mut color = Vec3::new(0.0, 0.0, 0.0);
            for _ in 0..SAMPLES_PER_PIXEL {
                let u_r: f32 = rand::thread_rng().gen();
                let v_r: f32 = rand::thread_rng().gen();

                let u = (x as f32 + u_r) / w as f32;
                let v = (y as f32 + v_r) / h as f32;

                let r = camera.ray(u, v);
                color += ray_color(&r, &scene, MAX_DEPTH);
            }

            color /= SAMPLES_PER_PIXEL as f32;

            let ir = prepare_color(color.r());
            let ig = prepare_color(color.g());
            let ib = prepare_color(color.b());

            println!("{} {} {}", ir, ig, ib);
        }
    }
}

fn prepare_color(component: f32) -> i32 {
    const GAMMA: f32 = 2.0;
    ((255.999 * component.powf(1.0 / GAMMA)) as i32).clamp(0, 255)
}

fn ray_color(ray: &Ray, scene: &Scene, depth: i32) -> Vec3 {
    use crate::geom::hittable::Hittable;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if depth <= 0 {
        return Vec3::new(0.0, 0.0, 0.0);
    }

    if let Some(hit) = scene.hit(ray, EPSILON, f32::INFINITY) {
        if let Some(scatter) = hit.material.scatter(ray, &hit) {
            return scatter.attenuation * ray_color(&scatter.scattered, scene, depth - 1);
        }
        return Vec3::new(0.0, 0.0, 0.0);
    }

    // Background color
    let t = 0.5 * (ray.direction.y + 1.0);
    (1.0 - t) * Vec3::new(1.0, 1.0, 1.0) + t * Vec3::new(0.5, 0.7, 1.0)
}

fn main() {
    render_ppm(1200, 800, 255);
}
