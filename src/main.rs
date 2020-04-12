#![feature(box_syntax)]
#![feature(clamp)]

mod environment;
mod geom;
mod ray;
mod vec3;

use environment::{Camera, Scene};
use geom::Sphere;
use ray::Ray;
use vec3::Vec3;

const SAMPLES_PER_PIXEL: u32 = 100;
const MAX_DEPTH: i32 = 50;

fn render_ppm(w: i32, h: i32, max_value: i32) {
    println!("P3\n{} {}\n{}", w, h, max_value);

    let camera = Camera::new_default();
    let mut scene = Scene::new();
    scene.add_solid(box Sphere::new(Vec3::new(0.0, 0.0, -1.0), 0.5));
    scene.add_solid(box Sphere::new(Vec3::new(0.0, -100.5, -1.0), 100.0));

    for y in (0..h).rev() {
        for x in 0..w {
            let mut color = Vec3::new(0.0, 0.0, 0.0);
            for _ in 0..SAMPLES_PER_PIXEL {
                use rand::Rng;

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
    use crate::ray::Hittable;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if depth <= 0 {
        return Vec3::new(0.0, 0.0, 0.0);
    }

    if let Some(hit) = scene.hit(ray, 0.0, f32::INFINITY) {
        let target = hit.point + hit.normal + Vec3::random_in_unit_sphere();
        return 0.5 * ray_color(&Ray::new(hit.point, target - hit.point), scene, depth - 1);
    }

    let t = 0.5 * (ray.direction.y + 1.0);
    (1.0 - t) * Vec3::new(1.0, 1.0, 1.0) + t * Vec3::new(0.5, 0.7, 1.0)
}

fn main() {
    render_ppm(400, 200, 255);
}
