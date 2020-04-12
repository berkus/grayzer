use crate::geom::hittable::Hit;
use crate::ray::Ray;
use crate::texture::material::{Material, Scatter};
use crate::vec3::Vec3;

pub struct Dielectric {
    pub refraction_index: f32,
}

impl Dielectric {
    pub fn new(refraction_index: f32) -> Self {
        Dielectric { refraction_index }
    }
}

impl Material for Dielectric {
    fn scatter(&self, ray_in: &Ray, hit: &Hit) -> Option<Scatter> {
        let etai_over_etat = if hit.front_face {
            1.0 / self.refraction_index
        } else {
            self.refraction_index
        };
        let refracted = Vec3::refract(ray_in.direction, hit.normal, etai_over_etat);
        let scattered = Ray::new(hit.point, refracted);
        return Some(Scatter::new(Vec3::new(1.0, 1.0, 1.0), scattered));
    }
}
