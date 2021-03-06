#ifndef UGDK_BASE_TEXTURECONTAINER_H_
#define UGDK_BASE_TEXTURECONTAINER_H_

#include <ugdk/base/resourcecontainer.h>
#include <ugdk/graphic.h>

namespace ugdk {
namespace base {

class TextureContainer : public ResourceContainer<graphic::Texture*> {
  public:
    graphic::Texture* Load(const std::string& filepath, const std::string& tag);
    graphic::Texture* Load(const std::string& filepath) {
        return Load(filepath, filepath);
    }
};

} // namespace base
} // namespace ugdk

#endif // UGDK_BASE_TEXTURECONTAINER_H_

