// Copyright © 2008-2021 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _SCENEGRAPH_BINARYCONVERTER_H
#define _SCENEGRAPH_BINARYCONVERTER_H

/**
 * Saving and loading a model from a binary format,
 * completely without Assimp
 * Nodes are expected to implement a Save method to
 * serialize their internals
 */

#include "BaseLoader.h"
#include "Billboard.h"
#include "CollisionGeometry.h"
#include "FileSystem.h"
#include "LOD.h"
#include "StaticGeometry.h"
#include "Thruster.h"
#include <functional>

namespace Serializer {
	class Reader;
	class Writer;
} // namespace Serializer

namespace SceneGraph {
	class Label3D;
	class Model;

	class BinaryConverter : public BaseLoader {
	public:
		BinaryConverter(Graphics::Renderer *);
		void Save(const std::string &filename, Model *m);
		void Save(const std::string &filename, const std::string &savepath, Model *m, const bool bInPlace);
		Model *Load(const std::string &filename);
		Model *Load(const std::string &filename, const std::string &path);
		Model *Load(const std::string &filename, RefCountedPtr<FileSystem::FileData> binfile);

		//if you implement any new node types, you must also register a loader function
		//before calling Load.
		void RegisterLoader(const std::string &typeName, std::function<Node *(NodeDatabase &)>);

	private:
		Model *CreateModel(const std::string &filename, Serializer::Reader &);
		void SaveMaterials(Serializer::Writer &, Model *m);
		void LoadMaterials(Serializer::Reader &);
		void SaveAnimations(Serializer::Writer &, Model *m);
		void LoadAnimations(Serializer::Reader &);
		ModelDefinition FindModelDefinition(const std::string &);

		Node *LoadNode(Serializer::Reader &);
		//this is a very simple loader so it's implemented here
		static Label3D *LoadLabel3D(NodeDatabase &);

		bool m_patternsUsed;
		std::map<std::string, std::function<Node *(NodeDatabase &)>> m_loaders;
	};
} // namespace SceneGraph

#endif
