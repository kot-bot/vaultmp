#ifndef NPCDB_H
#define NPCDB_H

#include <unordered_map>

#include "vaultmp.h"
#include "vaultserver.h"
#include "Database.h"
#include "Record.h"
#include "BaseContainer.h"
#include "Expected.h"

#include "sqlite/sqlite3.h"

/**
 * \brief Represents a NPC
 */

namespace DB
{
	class NPC
	{
		private:
			enum TplFlags : unsigned short
			{
				Traits    = 0x0001,
				Stats     = 0x0002,
				Factions  = 0x0004,
				Effects   = 0x0008,
				AIData    = 0x0010,
				AIPack    = 0x0020,
				Model     = 0x0040,
				Base      = 0x0080,
				Inventory = 0x0100,
				Script    = 0x0200,
			};

			static std::unordered_map<unsigned int, const NPC*> npcs;

			unsigned int baseID;
			bool essential;
			bool female;
			unsigned int race;
			unsigned int template_;
			unsigned short flags;
			unsigned int deathitem;

			mutable signed int new_female;
			mutable unsigned int new_race;

			NPC(const NPC&) = delete;
			NPC& operator=(const NPC&) = delete;

		public:
			static Expected<const NPC*> Lookup(unsigned int baseID);
			static Expected<const NPC*> GetNPCNotIn(const std::unordered_set<unsigned int>& _set, const std::function<bool(const NPC&)>& pred);

			unsigned int GetBase() const;
			bool IsEssential() const;
			bool IsFemale() const;
			bool IsOriginalFemale() const;
			unsigned int GetRace() const;
			unsigned int GetOriginalRace() const;
			unsigned int GetTemplate() const;
			unsigned short GetFlags() const;
			unsigned int GetDeathItem() const;
			const std::vector<const BaseContainer*>& GetBaseContainer() const;

			void SetRace(unsigned int race) const;
			void SetFemale(bool female) const;

			NPC(const std::string& table, sqlite3_stmt* stmt);
			~NPC() = default;
			// must never be called. only defined because vector requires it
			NPC(NPC&&) { std::terminate(); }
			NPC& operator=(NPC&&) = delete;
	};
}

#endif
