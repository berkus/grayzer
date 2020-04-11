use crate::ray::{Hittable, Hit, Ray};

pub struct Scene {
    pub solids: Vec<Box<dyn Hittable>>,
}

impl Scene {
    pub fn new() -> Self {
        Scene { solids: vec![] }
    }

    pub fn add_solid(&mut self, solid: Box<dyn Hittable>) {
        self.solids.push(solid);
    }
}

impl Hittable for Scene {
    fn hit(&self, ray: &Ray, t_min: f32, t_max: f32) -> Option<Hit> {
        let mut closest_so_far = t_max;
        let mut closest_hit: Option<Hit> = None;
        for solid in &self.solids {
            if let Some(hit) = solid.hit(ray, t_min, closest_so_far) {
                closest_so_far = hit.t;
                closest_hit = Some(hit);
            }
        }
        closest_hit
    }
}
