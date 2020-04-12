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

// Polynomial reflectivity approximation by Christophe Schlick
pub fn schlick(cosine: f32, refraction_index: f32) -> f32 {
    let r0 = (1.0 - refraction_index) / (1.0 + refraction_index);
    let r0 = r0 * r0;
    r0 + (1.0 - r0) * (1.0 - cosine).powi(5)
}
