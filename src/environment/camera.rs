use crate::ray::Ray;
use crate::vec3::{cross, Vec3};

pub struct Camera {
    pub origin: Vec3,
    pub lower_left_corner: Vec3,
    pub horizontal: Vec3,
    pub vertical: Vec3,
    pub lens_radius: f32,
    // Orthonormal basis
    pub u: Vec3,
    pub v: Vec3,
    pub w: Vec3,
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
        aperture: f32,
        focus_distance: f32,
    ) -> Self {
        let theta = vertical_fov.to_radians();
        let half_height = (theta / 2.0).tan();
        let half_width = aspect * half_height;

        let w = (look_from - look_at).normalized();
        let u = cross(view_up, w).normalized();
        let v = cross(w, u);

        Camera {
            origin: look_from,
            lower_left_corner: look_from
                - half_width * focus_distance * u
                - half_height * focus_distance * v
                - focus_distance * w,
            horizontal: 2.0 * half_width * focus_distance * u,
            vertical: 2.0 * half_height * focus_distance * v,
            lens_radius: aperture / 2.0,
            u,
            v,
            w,
        }
    }

    pub fn ray(&self, s: f32, t: f32) -> Ray {
        let rd = self.lens_radius * Vec3::random_in_unit_disk();
        let offset = self.u * rd.x + self.v * rd.y;
        Ray::new(
            self.origin + offset,
            self.lower_left_corner + s * self.horizontal + t * self.vertical - self.origin - offset,
        )
    }
}
