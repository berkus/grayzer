use crate::geom::hittable::Hit;
use crate::ray::Ray;
use crate::texture::material::{Material, Scatter};
use crate::vec3::{dot, Vec3};

pub struct Metal {
    pub albedo: Vec3,
    pub fuzz: f32,
}

impl Metal {
    pub fn new(albedo: Vec3, fuzz: f32) -> Self {
        let fuzz = if fuzz < 1.0 { fuzz } else { 1.0 };
        Metal { albedo, fuzz }
    }
}

impl Material for Metal {
    fn scatter(&self, ray_in: &Ray, hit: &Hit) -> Option<Scatter> {
        let reflected = Vec3::reflect(ray_in.direction, hit.normal);
        let scattered = Ray::new(
            hit.point,
            reflected + self.fuzz * Vec3::random_in_unit_sphere(),
        );
        if dot(scattered.direction, hit.normal) > 0.0 {
            return Some(Scatter::new(self.albedo, scattered));
        }
        return None;
    }
}
