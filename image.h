struct rgb {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct image_handle {
  unsigned int width;
  unsigned int height;
  struct rgb* pixels;
};

void print_image_as_ppm(struct image_handle img);
struct rgb make_random_color();
struct image_handle make_random_noise_image(int width, int height);