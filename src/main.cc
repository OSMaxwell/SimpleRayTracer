#include <camera.h>
#include <color.h>
#include <hittable_list.h>
#include <rtconst.h>
#include <sphere.h>

#include <iostream>

#define RED_RGB color(1, 0, 0)
#define GREEN_RGB color(1, 1, 1)

// @brief Sphere eq: t²b⋅b+ 2tb(A−C)+ (A−C)⋅(A−C)−r²=0 , t als unknown,
// b : direction,
// A-C : (Origin of sphere) - Center
double hit_sphere(const point3 &center, double radius, const ray &r) {
  // DOT same vector = length_squared
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared(); // (r.direction(), r.direction());
  // auto b = 2.0 * dot(oc, r.direction()); // inferred
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;
  // auto c = dot(oc, oc) - radius * radius;
  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0) { // Root or no solve --> Inside Sphere or not
    return -1.0;
  } else {
    return (-half_b - sqrt(discriminant)) / a;
  }
}

color ray_color(const ray &r, const hittable &world) {
  hit_record rec;
  if (world.hit(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + GREEN_RGB);
  }
  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); // Blend
}

int main() {
  // Image
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 20;

  // Camera
  auto viewport_height = 2.0;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length =
      1.0; // Simply how is far the plane from the camera of the viewport

  camera cam;

  // World
  hittable_list world;
  world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

  auto origin = point3(0, 0, 0);
  auto horizental = vec3(viewport_width, 0, 0);
  auto vertical = vec3(0, viewport_height, 0);
  auto lower_left_corner =
      origin - horizental / 2 - vertical / 2 - vec3(0, 0, focal_length);

  // Render
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' '
              << std::flush; // For the chosen PPM This is simply always the
    // same method of "rendering" an image
    for (int i = 0; i < image_width; ++i) {
      color pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; s++) { // Anti-aliasing.
        auto u = (i + random_double()) / (image_width - 1);
        auto v = (j + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world);
      }
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";
}