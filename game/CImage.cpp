#define QOI_IMPLEMENTATION

#include "CImage.h"
#include "CRenderer.h"

CImage::CImage(std::shared_ptr<CRenderer> renderer, const IFilesystem &filesystem, const fs::path &path)
{
    std::vector<byte> rawData = filesystem.Read(path);
    if (!rawData.size())
    {
        SPDLOG_CRITICAL("Image {} has no data", path.generic_string());
        std::terminate();
    }

    qoi_desc desc = {};
    void *data = qoi_decode(rawData.data(), rawData.size(), &desc, 4);
    if (!data)
    {
        SPDLOG_CRITICAL("Failed to decode image {}", path.generic_string());
        std::terminate();
    }
    if (desc.channels != 4)
    {
        SPDLOG_CRITICAL("Only RGBA images are supported, {} has {} channels", path.generic_string(), desc.channels);
        std::terminate();
    }

    rawData.clear();

    m_renderer = renderer;

    m_size = ivec2(desc.width, desc.height);
    m_texture = SDL_CreateTexture(m_renderer->GetRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
                                  desc.width, desc.height);
    if (!m_texture)
    {
        SPDLOG_CRITICAL("Failed to create texture for image {}: {}", path.generic_string(), SDL_GetError());
        std::terminate();
    }

    SDL_UpdateTexture(m_texture, nullptr, data, m_size.x * desc.channels);
    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);

    free(data);
}

CImage::~CImage()
{
    SDL_DestroyTexture(m_texture);
}

void CImage::Draw(const ivec2 &position, float zRotation, const vec2 &scale)
{
    vec2 finalSize = vec2(m_size) * scale;
    SDL_FRect srcRect = {0, 0, m_size.x, m_size.y};
    SDL_FRect destRect = {position.x, position.y, finalSize.x, finalSize.y};
    SDL_RenderTexture(m_renderer->GetRenderer(), m_texture, &srcRect, &destRect);
}
