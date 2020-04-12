use crate::ray::Ray;
use crate::vec3::{cross, Vec3};

pub struct Camera {
    pub origin: Vec3,
    pub lower_left_corner: Vec3,
    pub horizontal: Vec3,
    pub vertical: Vec3,
}

impl Camera {
    /// Create a free looking camera - look from look_from to point look_at, using view_up as
    /// the up direction.
    /// @param vertical_fov Vertical FOV, top to bottom, in degrees.
    /// @param aspect Width to height aspect ratio.
    pub fn new_free(
        look_from: Vec3,
        look_at: Vec3,
        view_up: Vec3,
        vertical_fov: f32,
        aspect: f32,
    ) -> Self {
        let theta = vertical_fov.to_radians();
        let half_height = (theta / 2.0).tan();
        let half_width = aspect * half_height;

        let w = (look_from - look_at).normalized();
        let u = cross(view_up, w).normalized();
        let v = cross(w, u);

        Camera {
            origin: look_from,
            lower_left_corner: look_from - half_width * u - half_height * v - w,
            horizontal: 2.0 * half_width * u,
            vertical: 2.0 * half_height * v,
        }
    }

    pub fn ray(&self, u: f32, v: f32) -> Ray {
        Ray::new(
            self.origin,
            self.lower_left_corner + u * self.horizontal + v * self.vertical - self.origin,
        )
    }
}
