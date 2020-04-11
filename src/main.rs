#![feature(box_syntax)]

mod environment;
mod geom;
mod ray;
mod vec3;

use environment::{Camera, Scene};
use geom::Sphere;
use ray::Ray;
use vec3::Vec3;

fn render_ppm(w: i32, h: i32, max_value: i32) {
    println!("P3\n{} {}\n{}", w, h, max_value);

    let camera = Camera::new_default();
    let mut scene = Scene::new();
    scene.add_solid(box Sphere::new(Vec3::new(0.0, 0.0, -1.0), 0.5));
    scene.add_solid(box Sphere::new(Vec3::new(0.0, -100.5, -1.0), 100.0));

    for y in (0..h).rev() {
        for x in 0..w {
            let u = x as f32 / w as f32;
            let v = y as f32 / h as f32;

            let r = camera.ray(u, v);
            let color = ray_color(&r, &scene);

            let ir = (255.999 * color.r()) as i32;
            let ig = (255.999 * color.g()) as i32;
            let ib = (255.999 * color.b()) as i32;

            println!("{} {} {}", ir, ig, ib);
        }
    }
}

fn ray_color(ray: &Ray, scene: &Scene) -> Vec3 {
    use crate::ray::Hittable;
    if let Some(hit) = scene.hit(ray, 0.0, f32::INFINITY) {
        return 0.5 * (hit.normal + Vec3::new(1.0, 1.0, 1.0));
    }

    let t = 0.5 * (ray.direction.y + 1.0);
    (1.0 - t) * Vec3::new(1.0, 1.0, 1.0) + t * Vec3::new(0.5, 0.7, 1.0)
}

fn main() {
    render_ppm(400, 200, 255);
}
