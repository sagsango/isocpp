#include <stdlib.h>
struct light {
  int green;
  int yellow;
  int red;
};

struct cross{
  struct light light;
  int id;
};

int main() {

  struct cross *ptr = (struct cross*) malloc(sizeof(struct cross));
  ptr->light = (struct light){ .green = 1, .yellow = 0, .red = 0 };
}
