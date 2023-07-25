/* vim: set et ts=8 sts=2 sw=2 : */

#include <SDL.h>

const char *RenderFlagsToString(Uint32 flags) {
  static char buf[256];
  int i=0;
  if (flags & SDL_RENDERER_SOFTWARE)
    i += sprintf(buf+i, "%s", ", software");
  if (flags & SDL_RENDERER_ACCELERATED)
    i += sprintf(buf+i, "%s", ", accelerated");
  if (flags & SDL_RENDERER_PRESENTVSYNC)
    i += sprintf(buf+i, "%s", ", vsync");
  if (flags & SDL_RENDERER_TARGETTEXTURE)
    i += sprintf(buf+i, "%s", ", render to texture");
  if (i == 0)
    return "";
  return buf + 2;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char **argv) {
  if (0 != SDL_Init(0)) {
    fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    return 1;
  }
  int nr = SDL_GetNumRenderDrivers();
  if (nr < 0) {
    fprintf(stderr, "SDL_GetNumRenderDrivers: %s\n", SDL_GetError());
    return 1;
  }
  printf("SDL_GetNumRenderDrivers: %d\n", nr);
  for (int i=0; i < nr; i++) {
    SDL_RendererInfo info = {0};
    if (0 > SDL_GetRenderDriverInfo(i, &info)) {
      fprintf(stderr, "SDL_GetRenderDriverInfo: %s\n", SDL_GetError());
      return 1;
    }
    printf("%s (%dx%d) [%s]\n", info.name, info.max_texture_width, info.max_texture_height, RenderFlagsToString(info.flags));
  }
  return 0;
}

