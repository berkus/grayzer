use crate::geom::hittable::{Hit, Hittable, WithNormal};
use crate::ray::Ray;
use crate::texture::material::Material;
use crate::vec3::{dot, Vec3};
use std::rc::Rc;

pub struct Sphere {
    center: Vec3,
    radius: f32,
    material: Rc<dyn Material>,
}

impl Sphere {
    pub fn new(center: Vec3, radius: f32, material: Rc<dyn Material>) -> Self {
        Sphere {
            center,
            radius,
            material,
        }
    }
}

impl WithNormal for Sphere {
    fn find_normal(&self, point: Vec3) -> Vec3 {
        (point - self.center) / self.radius
    }
}

impl Hittable for Sphere {
    fn hit(&self, ray: &Ray, t_min: f32, t_max: f32) -> Option<Hit> {
        let oc = ray.origin - self.center;
        let a = ray.direction.length_squared();
        let half_b = dot(oc, ray.direction);
        let c = oc.length_squared() - self.radius * self.radius;
        let discriminant = half_b * half_b - a * c;

        if discriminant < 0.0 {
            return None;
        }

        let root = discriminant.sqrt();
        let t = (-half_b - root) / a;

        if t < t_max && t > t_min {
            let point = ray.point_at(t);
            return Some(Hit::new(
                t,
                point,
                self.find_normal(point),
                ray,
                self.material.clone(),
            ));
        }

        let t = (-half_b + root) / a;

        if t < t_max && t > t_min {
            let point = ray.point_at(t);
            return Some(Hit::new(
                t,
                point,
                self.find_normal(point),
                ray,
                self.material.clone(),
            ));
        }

        return None;
    }
}
