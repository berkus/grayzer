mod geom;
mod vec3;
mod ray;

use vec3::Vec3;
use ray::Ray;
use geom::Sphere;

fn write_ppm(w: i32, h: i32, max_value: i32) {
    let lower_left_corner = Vec3::new(-2.0, -1.0, -1.0);
    let horizontal = Vec3::new(4.0, 0.0, 0.0);
    let vertical = Vec3::new(0.0, 2.0, 0.0);
    let origin = Vec3::new(0.0, 0.0, 0.0);

    println!("P3\n{} {}\n{}", w, h, max_value);

    for y in (0..h).rev() {
        for x in 0..w {
            let u = x as f32 / w as f32;
            let v = y as f32 / h as f32;

            let r = Ray::new(origin, lower_left_corner + u * horizontal + v * vertical);
            let color = ray_color(&r);

            let ir = (255.99 * color.r()) as i32;
            let ig = (255.99 * color.g()) as i32;
            let ib = (255.99 * color.b()) as i32;

            println!("{} {} {}", ir, ig, ib);
        }
    }
}

fn ray_color(ray: &Ray) -> Vec3 {
    use crate::ray::Hittable;
    let sphere = Sphere::new(Vec3::new(0.0,0.0,-1.0), 0.5);
    if let Some(hit) = sphere.hit(ray, 0.0, 1.0) {
        let n = (ray.point_at(hit.t) - Vec3::new(0.0, 0.0, -1.0)).normalized();
        return 0.5 * Vec3::new(n.x + 1.0, n.y + 1.0, n.z + 1.0);
    }

    let t = 0.5 * (ray.direction.y + 1.0);
    (1.0 - t) * Vec3::new(1.0, 1.0, 1.0) + t * Vec3::new(0.5, 0.7, 1.0)
}

fn main() {
    write_ppm(200, 100, 255);
}
