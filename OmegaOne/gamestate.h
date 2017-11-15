#ifndef _GAMESTATE_H
#define _GAMESTATE_H
#include <string>
#include <unordered_map>
#include <memory>
#include "entity.h"
#include "component.h"
#include "graphics.h"
#include "serialisation.h"
#include "file_log.h"
#include "movement.h"

class Level;
extern Level *g_level;

void Serialise(Archive *arch, Level& lvl, const var_info& info);

class Level 
{

public:

	Level(std::string name);

	void LoadDataToLevel();
	
	template <typename T>
	void AddComponent(const uint32_t ID, const uint32_t type);

	template <typename T>
	std::shared_ptr<T> GetComponent(const uint32_t ID, const uint32_t type);

	uint32_t AddEntity(uint32_t comp_handle);
	void InitTexture(std::string filename);

	template <typename T>
	void WriteSerialisedData(T* data, std::string filename, int save_mode);

	template <typename T>
	void LoadSerialisedData(T* data, const std::string filename, int save_mode);

	// helper functions
	std::unique_ptr<Texture>& GetTexture() { return m_texture; }

	friend void Serialise(Archive *arch, Level& lvl, const var_info& info);
	friend class Engine;

private:
	std::string m_name;
	int m_unid;
	
	// keep a list of textures
	std::unique_ptr<Texture> m_texture;

	// all the entites for this particular level
	std::unordered_map <uint32_t, std::unique_ptr<Entity> > m_entities;

	// all components associated with entites
	std::unordered_map <uint32_t, std::unordered_map<uint32_t, std::shared_ptr<Component> > > m_components;

};

template <typename T>
std::shared_ptr<T> Level::GetComponent(const uint32_t ID, const uint32_t type)
{
	return std::dynamic_pointer_cast<T>(m_components[ID][type]);
}

template <typename T>
void Level::AddComponent(const uint32_t ID, const uint32_t type)
{
	std::unordered_map<uint32_t, std::shared_ptr<Component> inner;
	inner.insert(std::make_pair(type, std::make_shared<T>()));
	m_components.insert(std::make_pair(ID, inner));
}

#endif // _GAMESTATE