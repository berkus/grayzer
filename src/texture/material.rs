use crate::geom::hittable::Hit;
use crate::ray::Ray;
use crate::vec3::Vec3;

pub struct Scatter {
    pub attenuation: Vec3,
    pub scattered: Ray,
}

impl Scatter {
    pub fn new(attenuation: Vec3, scattered: Ray) -> Self {
        Scatter {
            attenuation,
            scattered,
        }
    }
}

pub trait Material {
    fn scatter(&self, ray_in: &Ray, hit: &Hit) -> Option<Scatter>;
}
