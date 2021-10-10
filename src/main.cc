#include <color.h>
#include <ray.h>
#include <vec3.h>

#include <iostream>

color ray_color(const ray& r) {
  vec3 unit_direction = unit_vector(r.direction());  // einheitsvector
  auto t = 0.5 * (unit_direction.y() + 1.0);         // Scale
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); //blendedValue=(1−t)⋅startValue+t⋅endValue,
}

int main() {
  // Image

  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);

  // Camera
  auto viewport_height = 2;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length =
      1.0;  // Simply how is far the plane from the camera of the viewport.

  auto origin = point3(3, 3, 3);
  auto horizental = vec3(viewport_width, 0, 0);
  auto vertical = vec3(0, viewport_height, 0);
  auto lower_left_corner =
      origin - horizental / 2 - vertical / 2 - vec3(0, 0, focal_length);

  // Render
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' '
              << std::flush;  // For the chosen PPM This is simply always the
                              // same method of "rendering" an image
    for (int i = 0; i < image_width; ++i) {
      // auto r = double(i)/ (image_width-1);
      // auto g = double(j)/ (image_height-1);
      // auto b = 0.25;

      // int ir = static_cast<int>(255.999 * r);
      // int ig = static_cast<int>(255.999 * g);
      // int ib = static_cast<int>(255.999 * b);
      //   color pixel_color(double(i) / (image_width - 1),
      //                     double(j) / (image_height - 1), 0.25);
      auto u = double(i) / (image_width - 1);
      auto v = double(j) / (image_height - 1);
      ray r(origin, lower_left_corner + u * horizental + v * vertical - origin);
      color pixel_color = ray_color(r);

      // std::cout << ir << " "<< ig << " " << ib << std::endl;
      write_color(std::cout, pixel_color);
    }
  }
}