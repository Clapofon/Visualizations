#pragma once

#include <string>
#include <glm.hpp>

#include "FrameBuffer.h"
#include "SpriteBatch.h"
#include "tmx.h"
#include "Collider2D.h"

namespace Engine
{

    class Tilemap
    {
    public:
        Tilemap();
        ~Tilemap();

        void addMap(const std::string& fileName, const glm::vec2& position);

        bool draw(const std::string& map);
        bool draw(const std::string& map, const std::string& layer);
        void render(SpriteBatch& playerBatch);
        void update(Collider2D playerCollider);


    private:
        SpriteBatch m_batch;
        SpriteBatch m_upperBatch;
        SpriteBatch m_bathroomBatch;
        SpriteBatch m_karolroomBatch;
        SpriteBatch m_kitchenroomBatch;
        SpriteBatch m_tvroomBatch;
        SpriteBatch m_diningroomBatch;
        SpriteBatch m_stairsBatch;
        SpriteBatch m_bedroomBatch;
        SpriteBatch m_balconyBatch;
        SpriteBatch m_hallBatch;

        std::map<std::string, Tmx::Map*> m_maps;
        std::map<std::string, glm::vec2> m_positions;

        std::vector<std::pair<std::string, Collider2D>> m_colliders;
        
        std::string m_collision;
    };

}