struct RGB {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct ImageHandle {
  unsigned int width;
  unsigned int height;
  struct RGB* pixels;
};

void printImageAsPPM(struct ImageHandle img);
struct RGB makeRandomColor();
struct ImageHandle makeRandomNoiseImage(int width, int height);