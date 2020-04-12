use crate::ray::Ray;
use crate::texture::material::Material;
use crate::vec3::{dot, Vec3};
use std::rc::Rc;

pub struct Hit {
    pub point: Vec3,
    pub normal: Vec3,
    pub t: f32,
    pub front_face: bool,
    pub material: Rc<dyn Material>,
}

impl Hit {
    // The decision whether to have normals always point out or always point against the ray
    // is based on whether you want to determine the side of the surface at the time of geometry
    // or at the time of coloring. In this book we have more material types than we have geometry
    // types, so we'll go for less work and put the determination at geometry time. This is simply
    // a matter of preference and you'll see both implementations in the literature.
    pub fn new(
        t: f32,
        point: Vec3,
        outward_normal: Vec3,
        ray: &Ray,
        material: Rc<dyn Material>,
    ) -> Self {
        let front_face = dot(ray.direction, outward_normal) < 0.0;
        let normal = if front_face {
            outward_normal
        } else {
            -outward_normal
        };
        Hit {
            t,
            point,
            normal,
            front_face,
            material,
        }
    }
}

pub trait Hittable {
    /// Return Some(hit) if intersection found, None if not found.
    fn hit(&self, ray: &Ray, t_min: f32, t_max: f32) -> Option<Hit>;
}

pub trait WithNormal {
    fn find_normal(&self, point: Vec3) -> Vec3;
}
