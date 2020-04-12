use crate::geom::hittable::Hit;
use crate::ray::Ray;
use crate::texture::material::{Material, Scatter};
use crate::vec3::{dot, Vec3};

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

        let cos_theta = dot(-ray_in.direction, hit.normal).min(1.0);
        let sin_theta = (1.0 - cos_theta * cos_theta).sqrt();
        if etai_over_etat * sin_theta > 1.0 {
            // Could not refract, reflect instead.
            let reflected = Vec3::reflect(ray_in.direction, hit.normal);
            let scattered = Ray::new(hit.point, reflected);
            return Some(Scatter::new(Vec3::new(1.0, 1.0, 1.0), scattered));
        }

        let refracted = Vec3::refract(ray_in.direction, hit.normal, etai_over_etat);
        let scattered = Ray::new(hit.point, refracted);
        return Some(Scatter::new(Vec3::new(1.0, 1.0, 1.0), scattered));
    }
}
