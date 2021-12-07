#include "Tilemap.h"

#include "ResourceManager.h"
#include "Collision.h"

namespace Engine
{
    Tilemap::Tilemap()
    {
        m_batch.init();
        m_upperBatch.init();
        m_bathroomBatch.init();
        m_karolroomBatch.init();
        m_kitchenroomBatch.init();
        m_tvroomBatch.init();
        m_diningroomBatch.init();
        m_stairsBatch.init();
        m_bedroomBatch.init();
        m_balconyBatch.init();
        m_hallBatch.init();


        m_colliders.push_back(std::make_pair("bathroom", Collider2D(320, -192, 128, 128)));
        m_colliders.push_back(std::make_pair("bedroom", Collider2D(192, -768, 512, 128)));
        m_colliders.push_back(std::make_pair("karol_room", Collider2D(32, -352, 256, 256)));
        m_colliders.push_back(std::make_pair("kitchen", Collider2D(480, -192, 224, 128)));
        m_colliders.push_back(std::make_pair("tv_room", Collider2D(480, -448, 224, 244)));
        m_colliders.push_back(std::make_pair("dining_room", Collider2D(32, -608, 256, 256)));
        m_colliders.push_back(std::make_pair("stairs", Collider2D(448, -608, 256, 128)));
        m_colliders.push_back(std::make_pair("balcony", Collider2D(32, -768, 128, 128)));
        m_colliders.push_back(std::make_pair("hall", Collider2D(320, -608, 128, 384)));
    }

    Tilemap::~Tilemap()
    {

    }

    void Tilemap::addMap(const std::string& fileName, const glm::vec2& position)
    {
        auto it = m_positions.find(fileName);

        if (it == m_positions.end())
        {
            Tmx::Map* map = new Tmx::Map;
            map->ParseFile(fileName);
            m_maps.insert(make_pair(fileName, map));
            m_positions.insert(make_pair(fileName, position));
            draw(fileName);
        }
    }

    bool Tilemap::draw(const std::string& map)
    {
        //printf("kurwa\n");
        auto it = m_maps.find(map);

        if (it == m_maps.end())
        {
            return false;
        }
        else
        {
            auto pit = m_positions.find(map);
            
            if (pit == m_positions.end())
            {
                return false;
            }

            glm::vec2 pos = pit->second;

            Tmx::Map* tilemap = it->second;
            int width = tilemap->GetWidth();
            int height = tilemap->GetHeight();
            int tileHeight = tilemap->GetTileHeight();
            int tileWidth = tilemap->GetTileWidth();

            Engine::ColorRGBA8 color;
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = 255;
            m_batch.begin();
            m_upperBatch.begin();
            m_bathroomBatch.begin();
            m_karolroomBatch.begin();
            m_kitchenroomBatch.begin();
            m_tvroomBatch.begin();
            m_diningroomBatch.begin();
            m_stairsBatch.begin();
            m_bedroomBatch.begin();
            m_balconyBatch.begin();
            m_hallBatch.begin();
            for (int i = 0; i < tilemap->GetNumTileLayers(); i++)
            {
                for (int j = 0; j < height; j++)
                {
                    for (int k = 0; k < width; k++)
                    {
                        unsigned int gid = tilemap->GetTileLayer(i)->GetTileGid(j, k);
                        int tilesetIndex = tilemap->FindTilesetIndex(gid);

                        if (tilesetIndex != -1)
                        {
                          
                            glm::vec4 destRect((j * tileWidth) + pos.x, (-k * tileHeight) + pos.y, tileWidth, tileHeight);
                            std::string fileName = tilemap->FindTileset(gid)->GetImage()->GetSource();
                            int tilesetWidth = tilemap->FindTileset(gid)->GetColumns();
                            int tilesetHeight = tilemap->FindTileset(gid)->GetTileCount() / tilemap->FindTileset(gid)->GetColumns();

                            int firstGid = tilemap->FindTileset(gid)->GetFirstGid();
                            int tileId = gid - firstGid;

                            glm::vec2 minPos = glm::vec2(floor(tileId % tilesetWidth) / (float)tilesetWidth, floor(tileId / (float)tilesetWidth) / (float)tilesetHeight);
                            glm::vec2 maxPos = glm::vec2((floor(minPos.x + (float)tileWidth) / (float)tileWidth) / (float)tilesetWidth, (floor(minPos.y + (float)tileHeight) / (float)tileHeight) / (float)tilesetHeight);

                            /*std::cout << "minPos( " << minPos.x << ", " << minPos.y << ")" << std::endl
                                        << "maxPos( " << maxPos.x << ", " << maxPos.y << ")" << std::endl;*/

                            glm::vec4 uvRect(minPos.x, minPos.y, maxPos.x, maxPos.y);

                            std::string name = tilemap->GetTileLayer(i)->GetName();
                            if (name == "walls_up_enter_room")
                            {
                                color.a = 255;

                                m_upperBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);

                            }
                            else if (name == "walls_up_lazienka")
                            {
                                color.a = 255;
                                m_bathroomBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);
                            }
                            else if (name == "walls_up_kuchnia")
                            {
                                color.a = 255;
                                m_kitchenroomBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);
                            }
                            else if (name == "walls_up_salon")
                            {
                                color.a = 255;
                                m_tvroomBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);
                            }
                            else if (name == "walls_up_pokoj_goscinny")
                            {
                                color.a = 255;
                                m_diningroomBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);
                            }
                            else if (name == "walls_up_przedpokoj")
                            {
                                color.a = 255;
                                m_hallBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);
                            }
                            else if (name == "walls_up_sypialnia")
                            {
                                color.a = 255;
                                m_bedroomBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);
                            }
                            else if (name == "walls_up_balkon")
                            {
                                color.a = 255;
                                m_balconyBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);
                            }
                            else if (name == "walls_up_pokoj_karola")
                            {
                                color.a = 255;
                                m_karolroomBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);
                            }
                            else if (name == "walls_up_schody")
                            {
                                color.a = 255;
                                m_stairsBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);
                            }
                            else
                            {
                                color.a = 255;
                                
                                m_batch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);
                                
                            }                       
                        }
                    }
                }
            }
            m_batch.end();
            m_upperBatch.end();
            m_bathroomBatch.end();
            m_karolroomBatch.end();
            m_kitchenroomBatch.end();
            m_tvroomBatch.end();
            m_diningroomBatch.end();
            m_stairsBatch.end();
            m_bedroomBatch.end();
            m_balconyBatch.end();
            m_stairsBatch.end();
            m_hallBatch.end();

            return true;
        }
    }

    bool Tilemap::draw(const std::string& map, const std::string& layer)
    {
        auto it = m_maps.find(map);

        if (it == m_maps.end())
        {
            return false;
        }
        else
        {
            auto pit = m_positions.find(map);

            if (pit == m_positions.end())
            {
                return false;
            }

            glm::vec2 pos = pit->second;

            Tmx::Map* tilemap = it->second;
            int width = tilemap->GetWidth();
            int height = tilemap->GetHeight();
            int tileHeight = tilemap->GetTileHeight();
            int tileWidth = tilemap->GetTileWidth();

            Engine::ColorRGBA8 color;
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = 255;
            m_batch.begin();
            for (int j = 0; j < height; j++)
            {
                for (int k = 0; k < width; k++)
                {
                    int layerId = -1;
                    for (int i = 0; i < tilemap->GetNumTileLayers(); i++)
                    {
                        if (tilemap->GetTileLayer(i)->GetName() == layer)
                        {
                            layerId = i;
                        }
                    }
                    
                    if (layerId != -1)
                    {
                        unsigned int gid = tilemap->GetTileLayer(layerId)->GetTileGid(j, k);
                        int tilesetIndex = tilemap->FindTilesetIndex(gid);

                        if (tilesetIndex != -1)
                        {
                            glm::vec4 destRect((j * tileWidth) + pos.x, (-k * tileHeight) + pos.y, tileWidth, tileHeight);
                            std::string fileName = tilemap->FindTileset(gid)->GetImage()->GetSource();
                            int tilesetWidth = tilemap->FindTileset(gid)->GetColumns();
                            int tilesetHeight = tilemap->FindTileset(gid)->GetTileCount() / tilemap->FindTileset(gid)->GetColumns();

                            int firstGid = tilemap->FindTileset(gid)->GetFirstGid();
                            int tileId = gid - firstGid;

                            glm::vec2 minPos = glm::vec2(floor(tileId % tilesetWidth) / (float)tilesetWidth, floor(tileId / (float)tilesetWidth) / (float)tilesetHeight);
                            glm::vec2 maxPos = glm::vec2((floor(minPos.x + (float)tileWidth) / (float)tileWidth) / (float)tilesetWidth, (floor(minPos.y + (float)tileHeight) / (float)tileHeight) / (float)tilesetHeight);

                            /*std::cout << "minPos( " << minPos.x << ", " << minPos.y << ")" << std::endl
                                        << "maxPos( " << maxPos.x << ", " << maxPos.y << ")" << std::endl;*/

                            glm::vec4 uvRect(minPos.x, minPos.y, maxPos.x, maxPos.y);

                            m_batch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("assets/textures/" + fileName, false).id, 0.0f, color);
                        }
                    }
                }
            }
            m_batch.end();
            return true;
        }
    }

    void Tilemap::render(SpriteBatch& playerBatch)
    {
        m_batch.renderBatch();

        if (m_collision != "bathroom")
        {
            m_bathroomBatch.renderBatch();
        }
        if (m_collision != "karol_room")
        {
            m_karolroomBatch.renderBatch();
        }
        if (m_collision != "kitchen")
        {
            m_kitchenroomBatch.renderBatch();
        }
        if (m_collision != "tv_room")
        {
            m_tvroomBatch.renderBatch();
        }
        if (m_collision != "dining_room")
        {
            m_diningroomBatch.renderBatch();
        }
        if (m_collision != "stairs")
        {
            m_stairsBatch.renderBatch();
        }
        if (m_collision != "bedroom")
        {
            m_bedroomBatch.renderBatch();
        }
        if (m_collision != "balcony")
        {
            m_balconyBatch.renderBatch();
        }
        if (m_collision != "hall")
        {
            m_hallBatch.renderBatch();
        }
        playerBatch.renderBatch();

        m_upperBatch.renderBatch();
    }

    void Tilemap::update(Collider2D playerCollider)
    {
        for (int i = 0; i < m_colliders.size(); i++)
        {
            if (Collision::AABB(m_colliders[i].second, playerCollider))
            {
                m_collision = m_colliders[i].first;
            }
        }
    }
}