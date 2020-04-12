use crate::geom::hittable::Hit;
use crate::ray::Ray;
use crate::texture::material::{Material, Scatter};
use crate::vec3::Vec3;

pub struct Lambertian {
    pub albedo: Vec3,
}

impl Lambertian {
    pub fn new(albedo: Vec3) -> Self {
        Lambertian { albedo }
    }
}

impl Material for Lambertian {
    fn scatter(&self, _ray_in: &Ray, hit: &Hit) -> Option<Scatter> {
        let scatter_direction = hit.normal + Vec3::random_unit_vector();
        return Some(Scatter::new(
            self.albedo,
            Ray::new(hit.point, scatter_direction),
        ));
    }
}
