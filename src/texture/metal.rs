use crate::geom::hittable::Hit;
use crate::ray::Ray;
use crate::texture::material::{Material, Scatter};
use crate::vec3::{dot, Vec3};

pub struct Metal {
    pub albedo: Vec3,
}

impl Metal {
    pub fn new(albedo: Vec3) -> Self {
        Metal { albedo }
    }
}

impl Material for Metal {
    fn scatter(&self, ray_in: &Ray, hit: &Hit) -> Option<Scatter> {
        let reflected = Vec3::reflect(ray_in.direction, hit.normal);
        let scattered = Ray::new(hit.point, reflected);
        if dot(scattered.direction, hit.normal) > 0.0 {
            return Some(Scatter::new(self.albedo, scattered));
        }
        return None;
    }
}
