use core::ops;
use rand::Rng;
use std::f32::consts::PI;

#[derive(Debug, PartialEq, Copy, Clone)]
pub struct Vec3 {
    pub x: f32,
    pub y: f32,
    pub z: f32,
}

impl Vec3 {
    pub fn new(x: f32, y: f32, z: f32) -> Self {
        Self { x, y, z }
    }

    pub fn normalized(self) -> Self {
        self / self.length()
    }

    pub fn into_normalized(self) -> Self {
        let len = self.length();
        self / len
    }

    pub fn length(&self) -> f32 {
        self.length_squared().sqrt()
    }

    pub fn length_squared(&self) -> f32 {
        self.x * self.x + self.y * self.y + self.z * self.z
    }

    pub fn r(&self) -> f32 {
        self.x
    }
    pub fn g(&self) -> f32 {
        self.y
    }
    pub fn b(&self) -> f32 {
        self.z
    }

    pub fn random() -> Self {
        Self {
            x: rand::thread_rng().gen(),
            y: rand::thread_rng().gen(),
            z: rand::thread_rng().gen(),
        }
    }

    pub fn random_between(min: f32, max: f32) -> Self {
        Self {
            x: rand::thread_rng().gen_range(min, max),
            y: rand::thread_rng().gen_range(min, max),
            z: rand::thread_rng().gen_range(min, max),
        }
    }

    pub fn random_in_unit_sphere() -> Self {
        loop {
            let p = Vec3::random_between(-1.0, 1.0);
            if p.length_squared() < 1.0 {
                return p;
            }
        }
    }

    pub fn random_unit_vector() -> Self {
        let a = rand::thread_rng().gen_range(0.0, 2.0 * PI);
        let z: f32 = rand::thread_rng().gen_range(-1.0, 1.0);
        let r = (1.0 - z * z).sqrt();
        Vec3::new(r * a.cos(), r * a.sin(), z)
    }

    pub fn random_in_hemisphere(normal: Vec3) -> Self {
        let in_unit_sphere = Vec3::random_in_unit_sphere();
        return if dot(in_unit_sphere, normal) > 0.0 {
            // In the same hemisphere as the normal
            in_unit_sphere
        } else {
            -in_unit_sphere
        };
    }

    pub fn random_in_unit_disk() -> Self {
        loop {
            let random_x: f32 = rand::thread_rng().gen_range(-1.0, 1.0);
            let random_y: f32 = rand::thread_rng().gen_range(-1.0, 1.0);
            let p = Vec3::new(random_x, random_y, 0.0);
            if p.length_squared() < 1.0 {
                return p;
            }
        }
    }

    pub fn reflect(v: Vec3, normal: Vec3) -> Vec3 {
        v - 2.0 * dot(v, normal) * normal
    }

    pub fn refract(uv: Vec3, normal: Vec3, etai_over_etat: f32) -> Vec3 {
        let cos_theta = dot(-uv, normal);
        let r_out_parallel = etai_over_etat * (uv + cos_theta * normal);
        let r_out_perpendicular = -(1.0 - r_out_parallel.length_squared()).sqrt() * normal;
        r_out_parallel + r_out_perpendicular
    }
}

impl ops::Neg for Vec3 {
    type Output = Self;

    fn neg(self) -> Self::Output {
        Vec3 {
            x: -self.x,
            y: -self.y,
            z: -self.z,
        }
    }
}

impl ops::Add for Vec3 {
    type Output = Self;

    fn add(self, rhs: Self) -> Self::Output {
        Vec3 {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
            z: self.z + rhs.z,
        }
    }
}

impl ops::AddAssign for Vec3 {
    fn add_assign(&mut self, rhs: Self) {
        *self = *self + rhs;
    }
}

impl ops::Sub for Vec3 {
    type Output = Self;

    fn sub(self, rhs: Self) -> Self::Output {
        Vec3 {
            x: self.x - rhs.x,
            y: self.y - rhs.y,
            z: self.z - rhs.z,
        }
    }
}

impl ops::Mul<Vec3> for f32 {
    type Output = Vec3;

    fn mul(self, rhs: Vec3) -> Self::Output {
        Vec3 {
            x: self * rhs.x,
            y: self * rhs.y,
            z: self * rhs.z,
        }
    }
}

impl ops::Mul<f32> for Vec3 {
    type Output = Vec3;

    fn mul(self, rhs: f32) -> Self::Output {
        Vec3 {
            x: self.x * rhs,
            y: self.y * rhs,
            z: self.z * rhs,
        }
    }
}

impl ops::Mul<Vec3> for Vec3 {
    type Output = Vec3;

    fn mul(self, rhs: Vec3) -> Self::Output {
        Vec3 {
            x: self.x * rhs.x,
            y: self.y * rhs.y,
            z: self.z * rhs.z,
        }
    }
}

impl ops::Div<f32> for Vec3 {
    type Output = Vec3;

    fn div(self, rhs: f32) -> Self::Output {
        Vec3 {
            x: self.x / rhs,
            y: self.y / rhs,
            z: self.z / rhs,
        }
    }
}

impl ops::DivAssign<f32> for Vec3 {
    fn div_assign(&mut self, rhs: f32) {
        *self = *self / rhs;
    }
}

pub fn dot(lhs: Vec3, rhs: Vec3) -> f32 {
    lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z
}

pub fn cross(lhs: Vec3, rhs: Vec3) -> Vec3 {
    Vec3::new(
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x,
    )
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_vec3_add_vec3() {}

    #[test]
    fn test_vec3_mul_f32() {}
}
