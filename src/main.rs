mod vec3;
mod ray;

fn write_ppm(w: i32, h: i32, max_value: i32) {
    println!("P3\n{} {}\n{}", w, h, max_value);
    for y in (0..h).rev() {
        for x in 0..w {
            let r = x as f32 / w as f32;
            let g = y as f32 / h as f32;
            let b = 0.2_f32;

            let ir = (255.99 * r) as i32;
            let ig = (255.99 * g) as i32;
            let ib = (255.99 * b) as i32;

            println!("{} {} {}", ir, ig, ib);
        }
    }
}

fn main() {
    write_ppm(200, 200, 255);
}
