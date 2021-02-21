#include "EntityManager.h"
#include "Entity.h"



Entity EntityManager::Create()
{
    return Entity(&re);
}

Entity EntityManager::Create(const glm::vec2& pos, Tag tag, const glm::vec2& size)
{
   return Entity(&re,pos,tag,size);
}

entity_t EntityManager::RegistryCreate()
{
    entity_t retval = re.Create();
    AddComponent<Tag>(retval, Tag::None);
    AddComponent<Transform>(retval, glm::vec2(0,0), glm::vec2(100,100));
    return retval;
}

entity_t EntityManager::RegistryCreate(const glm::vec2& pos, Tag tag, const glm::vec2& size)
{
    entity_t retval = re.Create();
    AddComponent<Tag>(retval, tag);
    AddComponent<Transform>(retval, pos, size);
    return retval;
}
