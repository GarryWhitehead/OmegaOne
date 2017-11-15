#include "gamestate.h"

Level *g_level = nullptr;

Level::Level (std::string name) :	m_name(name),
									m_unid(0)
{
	g_level = this;
}

void Level::LoadDataToLevel()
{
	this->InitTexture("testsprite.png");

	this->LoadSerialisedData<Level>(this, "test-data", 0);

}

template <typename T>
void Level::WriteSerialisedData(T* data, const std::string filename, int save_mode)
{
	std::string path("assets/level/");
	std::fstream file;
	Archive *arch = nullptr;
	std::ios_base::openmode flags = std::fstream::out;
	if (save_mode)
	{
		//flags |= std::fstream::binary;
		//arch = new ArchiveBinary(file, FILE_OUT);
	}
	else
	{
		arch = new TextArchive(file, FileMode::FILE_OUT);
	}

	file.open(path + filename, flags);
	if (!file.is_open())
	{
		g_filelog->WriteLog("Critical error!! Unable create file for serialisation. Filename: " + filename + ".\n");
		exit(EXIT_FAILURE);
	}
	Serialise(arch, *data, var_info(""));
}

template <typename T>
void Level::LoadSerialisedData(T* data, const std::string filename, int save_mode)
{
	std::string path("assets/level/");
	std::fstream file;
	Archive *arch = nullptr;
	std::ios_base::openmode flags = std::fstream::in;
	if (save_mode)
	{
		//flags |= std::fstream::binary;
		//arch = new ArchiveBinary(file, FILE_IN);
	}
	else
	{
		arch = new TextArchive(file, FileMode::FILE_IN);
	}

	file.open(path + filename, flags);
	if (!file.is_open())
	{
		g_filelog->WriteLog("Critical error!! Unable to read file for serialisation. Filename: " + filename + ".\n");
		exit(EXIT_FAILURE);
	}

	Serialise(arch, *data, var_info(""));
}

uint32_t Level::AddEntity(uint32_t comp_handle = NO_COMPONENT)
{
	m_entities.insert(std::make_pair(m_unid, std::make_unique<Entity>(m_unid, comp_handle)));
	return ++m_unid;
}

void Level::InitTexture(std::string filename)
{
	m_texture = std::make_unique<Texture>();
	m_texture->LoadTextureFromFile(filename);
	m_texture->Init();
}

// Serialisation functions
void Serialise(Archive *arch, std::unordered_map<uint32_t, CompPtr>& mp, const var_info& info)
{
	uint32_t type;
	uint32_t sz = static_cast<uint32_t>(mp.size());
	Serialise(arch, sz, var_info(info.name + ".size"));

	auto iter = mp.begin();
	for (int c = 0; c < sz; ++c)
	{	
		if (mp.size() != sz)
		{
			Serialise(arch, type, var_info(info.name + "Key::[" + std::to_string(c) + "]"));
			if (type == SPRITE_COMPONENT)
				mp.insert(std::make_pair(type, std::make_shared<SpriteComponent>()));
			else if(type == MOVEMENT_COMPONENT)
				mp.insert(std::make_pair(type, std::make_shared<MoveComponent>()));

			Serialise(arch, *mp.at(type), var_info(info.name + "Data::[" + std::to_string(c) + "]"));
		}
		else
		{
			uint32_t type = iter->first;
			Serialise(arch, type, var_info(info.name + "Key::[" + std::to_string(c) + "]"));
			Serialise(arch, *iter->second, var_info(info.name + "Data::[" + std::to_string(c) + "]"));
		}
		++iter;
	}
}

void Serialise(Archive *arch, std::unordered_map<uint32_t, std::unordered_map<uint32_t, std::shared_ptr<Component> > >& mp, const var_info& info)
{
	uint32_t ID;
	uint32_t sz = static_cast<uint32_t>(mp.size());
	Serialise(arch, sz, var_info(info.name + ".size"));
	std::unordered_map<uint32_t, std::unordered_map<uint32_t, std::shared_ptr<Component> > >::iterator iter = mp.begin();
	for (int c = 0; c < sz; ++c)
	{
		if (mp.size() != sz)
		{
			std::unordered_map<uint32_t, CompPtr> inner_mp;
			Serialise(arch, ID, var_info(info.name + "Key::[" + std::to_string(c) + "]"));
			Serialise(arch, inner_mp, var_info(info.name + "Data::[" + std::to_string(c) + "]"));
			mp.insert(std::make_pair(ID, inner_mp));
		}
		else
		{
			ID = iter->first;
			Serialise(arch, ID, var_info(info.name + "Key::[" + std::to_string(c) + "]"));
			Serialise(arch, iter->second, var_info(info.name + "Data::[" + std::to_string(c) + "]"));
		}
		++iter;
	}
}

void Serialise(Archive *arch, std::unordered_map<uint32_t, std::unique_ptr<Entity> >& mp, const var_info& info)
{
	uint32_t ID;
	uint32_t sz = static_cast<uint32_t>(mp.size());
	Serialise(arch, sz, var_info(info.name + ".size"));

	std::unordered_map<uint32_t, std::unique_ptr<Entity> >::iterator iter = mp.begin();

	for(int c = 0; c < sz; ++c)
	{ 
		if (mp.size() != sz)
		{
			Serialise(arch, ID, var_info(info.name + "Key::[" + std::to_string(c) + "]"));
			mp.insert(std::make_pair(ID, std::make_unique<Entity>()));
			Serialise(arch, *mp.at(ID), var_info(info.name + "Data::[" + std::to_string(c) + "]"));
		}
		else
		{
			ID = iter->first;
			Serialise(arch, ID, var_info(info.name + "Key::[" + std::to_string(c) + "]"));
			Serialise(arch, *iter->second, var_info(info.name + "Data::[" + std::to_string(c) + "]"));
		}
		++iter;
	}
}

void Serialise(Archive *arch, Level& lvl, const var_info& info)
{
	Serialise(arch, lvl.m_entities, info.name + "m_entities");
	Serialise(arch, lvl.m_components, info.name + "m_components");
}