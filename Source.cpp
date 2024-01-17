#include <string>
#include <fstream>
#include <iostream>
#include <signal.h>
#include <vector>
#include "enet/include/enet.h"
#include <nlohmann/json.hpp>
#include "ItsKyyStore/Item.h"
#include "ItsKyyStore/Base.h"
#include "ItsKyyStore/Player.h"
#include "ItsKyyStore/Packet.h"
#include "ItsKyyStore/Guilds.h"
#include "ItsKyyStore/World.h"
#include "ItsKyyStore/Algorithm.h"
#include "proton/Variant.hpp"
#include "proton/Vector.hpp"
#pragma comment(lib, "Ws2_32.lib")
BOOL WINAPI HandlerRoutine(DWORD dwCtrlType) {
	save_all();
	return FALSE;
}
vector<string> split_string_by_newline(const string& str)
{
	auto result = vector<string>{};
	auto ss = stringstream{ str };

	for (string line; getline(ss, line, '\n');)
		result.push_back(line);

	return result;
}

//ENetPeer* peer
long long last_time = 0, last_guild_save = time(NULL) + 60, last_time_ = 0, last_time2_ = 0, last_world_menu = 0, last_honors_reset = 0, autofarm_delay = 0, last_hm_time = 0, last_growganoth_time = 0;
void loop_cheat(ENetPeer* peer) {
	long long ms_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	try {
		if (autofarm_delay - ms_time <= 0) {
			autofarm_delay = ms_time + 500;
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world.empty() or pInfo(currentPeer)->tankIDName.empty()) continue;
				if (not has_playmod(pInfo(currentPeer), "Cheat Active: Auto Farm")) continue;
				bool isRemote = pInfo(currentPeer)->isRemote;
				// Auto Farm
				string name_ = pInfo(currentPeer)->world;
				vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
				if (p != worlds.end()) {
					World* world_ = &worlds[p - worlds.begin()];
					if (pInfo(currentPeer)->Cheat_AF_PlantingTree != 0 and pInfo(currentPeer)->Cheat_AF_isRunning) {
						string name_ = pInfo(currentPeer)->world;
						vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
						if (p != worlds.end()) {
							World* world_ = &worlds[p - worlds.begin()];
							WorldBlock* block_ = &world_->blocks[pInfo(currentPeer)->Cheat_AF_PunchX + (pInfo(currentPeer)->Cheat_AF_PunchY * 100)];
							if (block_->fg == 0 and block_->bg == 0) {
								if (items[pInfo(currentPeer)->Cheat_AF_PlantingTree].blockType == BlockTypes::CLOTHING) {
									pInfo(currentPeer)->Cheat_AF_PlantingTree = 0;
									break;
								}
								int adaBrp = 0;
								modify_inventory(currentPeer, pInfo(currentPeer)->Cheat_AF_PlantingTree, adaBrp);
								if (adaBrp == 0) break;
								if (!isRemote and has_playmod(pInfo(currentPeer), "rayman's fist") and adaBrp < 3) break;
								if (!isRemote and pInfo(currentPeer)->hand == 9918 and adaBrp < 5) break;
								if (!isRemote and pInfo(currentPeer)->hand == 9772 and adaBrp < 4) break;
								if (!isRemote and pInfo(currentPeer)->hand == 9770 and adaBrp < 7) break;
								if (!isRemote and pInfo(currentPeer)->hand == 9906 and adaBrp < 7) break;
								if (!isRemote and pInfo(currentPeer)->hand == 9908 and adaBrp < 10) break;
								if (!isRemote and pInfo(currentPeer)->hand == 9846 and adaBrp < 10) break;

								//FOR AUTO BREAK+PLACE
								if (has_playmod(pInfo(currentPeer), "rayman's fist")) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
									else {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
								}
								//5 FAR
								if (pInfo(currentPeer)->hand == 9918) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 4, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
									else {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 4, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
								}
								//4 FAR
								else if (pInfo(currentPeer)->hand == 9772) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
									else {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
								}
								//7 FAR
								else if (pInfo(currentPeer)->hand == 9770) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 4, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 5, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 6, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
									else {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 4, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 5, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 6, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
								}
								else if (pInfo(currentPeer)->hand == 9906) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 4, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 5, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 6, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
									else {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 4, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 5, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 6, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
								}

								//10 FAR
								else if (pInfo(currentPeer)->hand == 9908) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 4, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 5, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 6, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 7, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 8, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 9, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
									else {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 4, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 5, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 6, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 7, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 8, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 9, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
								}
								else if (pInfo(currentPeer)->hand == 9846) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 4, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 5, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 6, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 7, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 8, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 9, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
									else {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 4, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 5, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 6, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 7, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 8, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 9, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
								}

								else {
									if (!isRemote and adaBrp < 2) break;
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
									else {
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
										autoPlace_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY, pInfo(currentPeer)->Cheat_AF_PlantingTree);
									}
								}
							}
							else {//FOR AUTO BREAK
								if (has_playmod(pInfo(currentPeer), "rayman's fist")) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
									else {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
								}
								//5 FAR
								if (pInfo(currentPeer)->hand == 9918) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 4, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
									else {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 4, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
								}
								//4 FAR
								else if (pInfo(currentPeer)->hand == 9772) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
									else {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
								}
								//7 FAR
								else if (pInfo(currentPeer)->hand == 9770) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 4, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 5, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 6, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
									else {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 4, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 5, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 6, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
								}
								else if (pInfo(currentPeer)->hand == 9906) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 4, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 5, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 6, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
									else {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 4, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 5, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 6, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
								}
								//10 FAR
								else if (pInfo(currentPeer)->hand == 9908) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 4, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 5, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 6, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 7, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 8, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 9, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
									else {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 4, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 5, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 6, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 7, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 8, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 9, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
								}
								else if (pInfo(currentPeer)->hand == 9846) {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 3, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 4, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 5, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 6, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 7, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 8, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 9, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
									else {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 2, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 3, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 4, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 5, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 6, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 7, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 8, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 9, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
								}

								else {
									if (pInfo(currentPeer)->isFacingLeft) {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX - 1, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
									else {
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX, pInfo(currentPeer)->Cheat_AF_PunchY);
										autoPunch_tile(currentPeer, pInfo(currentPeer)->Cheat_AF_PunchX + 1, pInfo(currentPeer)->Cheat_AF_PunchY);
									}
								}
							}
						}
					}
				}
			}
		}
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world.empty() or pInfo(currentPeer)->tankIDName.empty()) continue;
			if (not has_playmod(pInfo(currentPeer), "Cheat Active: Auto Spam")) continue;
			string name_ = pInfo(currentPeer)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				if (has_playmod(pInfo(currentPeer), "Cheat Active: Auto Spam")) {
					if (duration_cast<seconds>(system_clock::now().time_since_epoch()).count() > pInfo(currentPeer)->Cheat_Last_Spam) {
						pInfo(currentPeer)->Cheat_Last_Spam = duration_cast<seconds>(system_clock::now().time_since_epoch()).count() + pInfo(currentPeer)->Cheat_Spam_Delay;
						string msg = pInfo(currentPeer)->Cheat_Spam_Text;
						if (pInfo(currentPeer)->tankIDName == "") break;
						if (msg.length() <= 0 || msg.length() > 120 || msg.empty() || std::all_of(msg.begin(), msg.end(), [](char c) {return std::isspace(c); })) continue;
						for (char c : msg) if (c < 0x20 || c > 0x7A) continue;
						space_(msg);
						if (msg[0] == '/') SendCmd(currentPeer, msg);
						else {
							if (msg[0] == '`' and msg.size() <= 2) break;
							if (pInfo(currentPeer)->world == "") break;
							if (has_playmod(pInfo(currentPeer), "duct tape") || has_playmod(pInfo(currentPeer), "Iron MMMFF")) {
								string msg2 = "";
								for (int i = 0; i < msg.length(); i++) {
									if (isspace(msg[i])) msg2 += " ";
									else {
										if (isupper(msg[i])) msg2 += i % 2 == 0 ? "M" : "F";
										else msg2 += i % 2 == 0 ? "m" : "f";
									}
								}
								msg = msg2;
							}
							string check_ = msg;
							transform(check_.begin(), check_.end(), check_.begin(), ::tolower);
							{
								string name_ = pInfo(currentPeer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									if (world_->silence and pInfo(currentPeer)->superdev != 1 and world_->owner_name != pInfo(currentPeer)->tankIDName and find(world_->admins.begin(), world_->admins.end(), pInfo(currentPeer)->tankIDName) == world_->admins.end()) {
										gamepacket_t p;
										p.Insert("OnTalkBubble"), p.Insert(pInfo(currentPeer)->netID), p.Insert("`1(Peasants must not speak)"), p.Insert(1), p.CreatePacket(currentPeer);
										break;
									}
								}
							}
							replaceAll(msg, "`%", "");
							string chat_color = "`$";
							if (pInfo(currentPeer)->d_name.empty()) {
								chat_color = pInfo(currentPeer)->superdev ? "`5" : pInfo(currentPeer)->dev ? "`^" : pInfo(currentPeer)->tmod ? "`^" : "`$";
							}
							if (has_playmod(pInfo(currentPeer), "Infected!")) {
								chat_color = "`2";
								if (rand() % 4 < 1) chat_color += "Brraaiinnss...";
							}
							if (pInfo(currentPeer)->face == 1170)  chat_color = "`4";
							gamepacket_t p, p2;
							p.Insert("OnConsoleMessage");
							p.Insert("CP:_PL:0_OID:_CT:[W]_ `6<`w" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + (pInfo(currentPeer)->is_legend ? " of Legend" : "") + "`6> " + chat_color + msg);
							p2.Insert("OnTalkBubble");
							p2.Insert(pInfo(currentPeer)->netID);
							if (check_ != ":/" and check_ != ":p" and check_ != ":*" and check_ != ";)" and check_ != ":d" and check_ != ":o" and check_ != ":'(" and check_ != ":(") {
								p2.Insert("CP:_PL:0_OID:_player_chat=" + (chat_color == "`$" ? "" : chat_color) + msg);
							}
							else p2.Insert(msg);
							for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
								if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
								if (pInfo(currentPeer2)->world == pInfo(currentPeer)->world) {
									bool muted_ = false;
									for (int c_ = 0; c_ < pInfo(currentPeer2)->friends.size(); c_++) {
										if (pInfo(currentPeer2)->friends[c_].name == pInfo(currentPeer)->tankIDName) {
											if (pInfo(currentPeer2)->friends[c_].mute) {
												muted_ = true;
												break;
											}
										}
									}
									if (not muted_ and not pInfo(currentPeer)->Cheat_HideChat) {
										p.CreatePacket(currentPeer2);
										p2.CreatePacket(currentPeer2);
									}
								}
							}
						}
						break;
					}
				}
			}
		}
	}
	catch (out_of_range& sui) {
		xItsCrims_warn(sui.what());
	}
}
void loop_spammer() {
	while (true) {
		std::this_thread::sleep_for(seconds(5)); // 5 Seconds
		try {
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world.empty() or pInfo(currentPeer)->tankIDName.empty()) continue;
				string name_ = pInfo(currentPeer)->world;
				vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
				if (p != worlds.end()) {
					if (pInfo(currentPeer)->npc_summon) {
						if (pInfo(currentPeer)->npc_text != "") {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(currentPeer)->npc_netID);
							p.Insert(pInfo(currentPeer)->npc_text);
							p.Insert(0), p.Insert(0);

							gamepacket_t p2;
							p2.Insert("OnConsoleMessage");
							p2.Insert("CP:_PL:0_OID:_CT:[W]_ `6<`w" + pInfo(currentPeer)->npc_name + "`6> " + pInfo(currentPeer)->npc_text + "");

							for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
								if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
								if (pInfo(currentPeer2)->world != pInfo(currentPeer2)->npc_world) continue;

								p.CreatePacket(currentPeer2);
								p2.CreatePacket(currentPeer2);
							}
						}
					}
				}
			}

		}


		catch (const std::out_of_range& e) {
			std::cout << e.what() << std::endl;
		}
	}
}

void biar_jalan() {
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(550));
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (pInfo(currentPeer)->world != "" && pInfo(currentPeer)->Cheat_AF) {
				loop_cheat(currentPeer);
			}
		}
	}
}
void loop_worlds() {
	long long ms_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(), time_ = time(nullptr);
	if (last_hm_time - ms_time <= 0) {
		last_hm_time = ms_time + 60000;
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world.empty() or pInfo(currentPeer)->tankIDName.empty() or pInfo(currentPeer)->dev or pInfo(currentPeer)->superdev or find(Access.begin(), Access.end(), pInfo(currentPeer)->tankIDName) != Access.end() or find(xItsCrims.begin(), xItsCrims.end(), pInfo(currentPeer)->tankIDName) != xItsCrims.end()) continue;
			if (pInfo(currentPeer)->hack_ != 0) pInfo(currentPeer)->hack_ = 0;
			// Leaderboard System & Update
			int adaBrpWL = 0, adaBrpDL = 0, adaBrpBGL = 0, totalBank = 0;
			int adaBrpGemsKeWL = pInfo(currentPeer)->gems / 2000;
			modify_inventory(currentPeer, 242, adaBrpWL), modify_inventory(currentPeer, 1796, adaBrpDL), modify_inventory(currentPeer, 7188, adaBrpBGL);
			if (adaBrpBGL != 0) adaBrpWL += adaBrpBGL * 10000;
			if (adaBrpDL != 0) adaBrpWL += adaBrpDL * 100;
			pInfo(currentPeer)->totalWls = adaBrpWL;
			pInfo(currentPeer)->totalNetWorth = adaBrpGemsKeWL + adaBrpWL;
			string find = pInfo(currentPeer)->tankIDName;
			vector<pair<long long int, string>>::iterator lb = find_if(top_richest.begin(), top_richest.end(), [find](const pair <long long int, string>& element) { return element.second == find; });
			if (lb != top_richest.end()) top_richest[lb - top_richest.begin()].first = pInfo(currentPeer)->totalNetWorth;
			else top_richest.push_back(make_pair(pInfo(currentPeer)->totalNetWorth, find));
			update_leaderboard();
			save_leaderboard();
		}
	}
	if (last_hm_time - ms_time <= 0) {
		last_hm_time = ms_time + 60000;
		for (int i = 0; i < monitors.size(); i++) {
			string name_ = monitors[i].world_name;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds[p - worlds.begin()];
				WorldBlock* monitor = &world_->blocks[monitors[i].x + (monitors[i].y * 100)];
				if (!items[monitor->fg].heart_monitor) {
					monitors.erase(monitors.begin() + i);
					i--;
					continue;
				}
				monitors[i].active = 0;
				string find_mon = monitor->heart_monitor;
				if (find_mon.size() >= 2) find_mon.resize(find_mon.size() - 2); // remove `` is galo
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName == find_mon) {
						monitors[i].active = 1;
						break;
					}
				}
				PlayerMoving data_{};
				data_.packetType = 5, data_.punchX = monitors[i].x, data_.punchY = monitors[i].y, data_.characterState = 0x8;
				BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, monitor));
				BYTE* blc = raw + 56;
				form_visual(blc, *monitor, *world_, NULL, false, false, monitors[i].x, monitors[i].y);
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->world == world_->name) {
						send_raw(currentPeer, 4, raw, 112 + alloc_(world_, monitor), ENET_PACKET_FLAG_RELIABLE);
					}
				}
				delete[] raw, blc;
			}
		}
	}
	if (last_time2_ - ms_time <= 0 && restart_server_status) {
		gamepacket_t p;
		p.Insert("OnConsoleMessage"), p.Insert("`4Global System Message``: Restarting server for update in `4" + to_string(restart_server_time) + "`` minutes");
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			packet_(currentPeer, "action|play_sfx\nfile|audio/ogg/suspended.ogg\ndelayMS|700");
			p.CreatePacket(currentPeer);
		}
		restart_server_time -= 1;
		if (restart_server_time == 0) {
			last_time2_ = ms_time + 10000, restart_server_status_seconds = true, restart_server_status = false;
			restart_server_time = 50;
		}
		else last_time2_ = ms_time + 60000;
	}
	if (restart_server_status_seconds && last_time2_ - ms_time <= 0) {
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			gamepacket_t p;
			p.Insert("OnConsoleMessage"), p.Insert("`4Global System Message``: Restarting server for update in `4" + (restart_server_time > 0 ? to_string(restart_server_time) : "ZERO") + "`` seconds" + (restart_server_time > 0 ? "" : "! Should be back up in a minute or so. BYE!") + "");
			p.CreatePacket(currentPeer);
		}
		last_time2_ = ms_time + 10000;
		if (restart_server_time == 0) {
			restart_server_status_seconds = false;
			trigger_save_();
		}
		restart_server_time -= 10;
	}
	if (last_honors_reset - ms_time <= 0) {
		honors_reset();
		last_honors_reset = ms_time + 3600000;
	}
	if (last_world_menu - ms_time <= 0) {
		fstream newfile;
		newfile.open("database/deposit.txt", ios::in);
		if (newfile.is_open()) {
			newfile >> depositworld;
			newfile.close();
		}
		//cout << "r w " << endl;
		active_world_list = "";
		active_world_list.clear();
		sort(top_active_worlds.begin(), top_active_worlds.end());
		reverse(top_active_worlds.begin(), top_active_worlds.end());
		top_active_worlds.resize((top_active_worlds.size() >= 24 ? 24 : top_active_worlds.size()));
		for (uint8_t i = 0; i < top_active_worlds.size(); i++) {
			int w_cz = 0;
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != top_active_worlds[i].second) continue;
				w_cz++;
			}
			active_world_list += "\nadd_floater|" + top_active_worlds[i].second + "|" + to_string(w_cz) + "|" + to_string(0.5 - (i * 0.005)) + "|3529161471";
		}
		top_active_worlds.clear();
		if (active_world_list.empty()) active_world_list = "\nadd_floater|START|0|0.5|3529161471";
		last_world_menu = ms_time + 60000;
		//cout << "d w" << endl;
	}
	if (last_time - ms_time <= 0) {
		last_time = ms_time + 1300;
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world.empty() or pInfo(currentPeer)->tankIDName.empty()) continue;
			if (pInfo(currentPeer)->last_fish_catch + pInfo(currentPeer)->fish_seconds < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() && pInfo(currentPeer)->fishing_used != 0 && rand() % 100 < (pInfo(currentPeer)->hand == 3010 ? 9 : 6)) {
				PlayerMoving data_{};
				data_.packetType = 17, data_.netID = 34, data_.YSpeed = 34, data_.x = pInfo(currentPeer)->f_x * 32 + 16, data_.y = pInfo(currentPeer)->f_y * 32 + 16;
				pInfo(currentPeer)->last_fish_catch = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				BYTE* raw = packPlayerMoving(&data_);
				gamepacket_t p3(0, pInfo(currentPeer)->netID);
				p3.Insert("OnPlayPositioned"), p3.Insert("audio/splash.wav");
				for (ENetPeer* currentPeer_event = server->peers; currentPeer_event < &server->peers[server->peerCount]; ++currentPeer_event) {
					if (currentPeer_event->state != ENET_PEER_STATE_CONNECTED or currentPeer_event->data == NULL or pInfo(currentPeer_event)->world != pInfo(currentPeer)->world) continue;
					send_raw(currentPeer_event, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE), p3.CreatePacket(currentPeer_event);
				}
				delete[] raw;
			}
			
			string name_ = pInfo(currentPeer)->world;
			vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (p != worlds.end()) {
				World* world_ = &worlds[p - worlds.begin()];
				if (world_->special_event && world_->last_special_event + 30000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						gamepacket_t p, p2;
						p.Insert("OnAddNotification"), p.Insert("interface/large/special_event.rttex"), p.Insert("`2" + items[world_->special_event_item].event_name + ":`` " + (items[world_->special_event_item].event_total == 1 ? "`oTime's up! Nobody found it!``" : "`oTime's up! " + to_string(world_->special_event_item_taken) + " of " + to_string(items[world_->special_event_item].event_total) + " items found.``") + ""), p.Insert("audio/cumbia_horns.wav"), p.Insert(0);
						p2.Insert("OnConsoleMessage"), p2.Insert("`2" + items[world_->special_event_item].event_name + ":`` " + (items[world_->special_event_item].event_total == 1 ? "`oTime's up! Nobody found it!``" : "`oTime's up! " + to_string(world_->special_event_item_taken) + " of " + to_string(items[world_->special_event_item].event_total) + " items found.``") + "");
						for (ENetPeer* currentPeer_event = server->peers; currentPeer_event < &server->peers[server->peerCount]; ++currentPeer_event) {
							if (currentPeer_event->state != ENET_PEER_STATE_CONNECTED or currentPeer_event->data == NULL or pInfo(currentPeer_event)->world != name_) continue;
							p.CreatePacket(currentPeer_event), p2.CreatePacket(currentPeer_event);
							PlayerMoving data_{};
							data_.effect_flags_check = 1, data_.packetType = 14, data_.netID = 0;
							for (int i_ = 0; i_ < world_->drop.size(); i_++) {
								if (world_->drop[i_].special == true) {
									data_.plantingTree = world_->drop[i_].uid;
									BYTE* raw = packPlayerMoving(&data_);
									send_raw(currentPeer_event, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									delete[]raw;
									world_->drop[i_].id = 0, world_->drop[i_].x = -1, world_->drop[i_].y = -1;
								}
							}
						}
						world_->last_special_event = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count(), world_->special_event_item = 0, world_->special_event_item_taken = 0, world_->special_event = false;
					}
				}
			if (pInfo(currentPeer)->hand == 3578 && pInfo(currentPeer)->hand_torch + 60000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
				if (pInfo(currentPeer)->hand_torch != 0) {
					int got = 0;
					modify_inventory(currentPeer, 3578, got);
					if (got - 1 >= 1) {
						gamepacket_t p;
						p.Insert("OnTalkBubble"), p.Insert(pInfo(currentPeer)->netID), p.Insert("`4My torch went out, but I have " + to_string(got - 1) + " more!``"), p.CreatePacket(currentPeer);
					}
					modify_inventory(currentPeer, 3578, got = -1);
				}
				pInfo(currentPeer)->hand_torch = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			}
			if (pInfo(currentPeer)->world != "" && pInfo(currentPeer)->Cheat_AF) {
				if (pInfo(currentPeer)->isRemote == 1) {
					if (pInfo(currentPeer)->Cheat_AF_isRunning + 5 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						if (pInfo(currentPeer)->Cheat_AF_isRunning != 0) {
							if (pInfo(currentPeer)->magnetron_id >= 1) {
								loop_cheat(currentPeer);
							}
							else {
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(currentPeer)->netID), p.Insert("`wMagplant 5000 `4Empty``"), p.CreatePacket(currentPeer);
							}
						}
					}
					pInfo(currentPeer)->Cheat_AF_isRunning = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				}
				else {
					if (pInfo(currentPeer)->Cheat_AF_isRunning + 5 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						if (pInfo(currentPeer)->Cheat_AF_isRunning != 0) {
							loop_cheat(currentPeer);
						}
					}
					pInfo(currentPeer)->Cheat_AF_isRunning = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				}
			}
			if (pInfo(currentPeer)->rb == 1 && pInfo(currentPeer)->name_time + 250 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
				pInfo(currentPeer)->name_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				string msg2 = pInfo(currentPeer)->name_color;
				if (pInfo(currentPeer)->is_legend) msg2 = "`" + to_string(rand() % 9 + 1) + pInfo(currentPeer)->tankIDName;
				else for (int i = 0; i < pInfo(currentPeer)->tankIDName.length(); i++) msg2 += "`" + to_string(rand() % 9 + 1) + "" + pInfo(currentPeer)->tankIDName[i];
				ChangeName(currentPeer, msg2);
			}
			if (pInfo(currentPeer)->hand == 2204 and pInfo(currentPeer)->x != -1 and pInfo(currentPeer)->y != -1) {
				if (not has_playmod(pInfo(currentPeer), "Irradiated")) {
					if (pInfo(currentPeer)->geiger_x == -1 and pInfo(currentPeer)->geiger_y == -1) pInfo(currentPeer)->geiger_x = (rand() % 100) * 32, pInfo(currentPeer)->geiger_y = (rand() % 54) * 32;
					int a_ = pInfo(currentPeer)->geiger_x + ((pInfo(currentPeer)->geiger_y * 100) / 32), b_ = pInfo(currentPeer)->x + ((pInfo(currentPeer)->y * 100) / 32), diff = abs(a_ - b_) / 32;
					if (diff > 30) { // nieko

					}
					else if (diff >= 30) { // raudona
						if (pInfo(currentPeer)->geiger_time + 1500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
							pInfo(currentPeer)->geiger_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
							PlayerMoving data_{};
							data_.packetType = 17, data_.x = pInfo(currentPeer)->x + 10, data_.y = pInfo(currentPeer)->y + 16, data_.characterState = 0x8, data_.XSpeed = 0, data_.YSpeed = 114;
							BYTE* raw = packPlayerMoving(&data_, 56);
							raw[3] = 114;
							double rotation = -4.13;
							memcpy(raw + 40, &rotation, 4);
							send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
							delete[] raw;
						}
					}
					else if (diff >= 15) { // geltona
						if (pInfo(currentPeer)->geiger_time + 1500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
							pInfo(currentPeer)->geiger_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
							PlayerMoving data_{};
							data_.packetType = 17, data_.x = pInfo(currentPeer)->x + 10, data_.y = pInfo(currentPeer)->y + 16, data_.characterState = 0x8, data_.XSpeed = 1, data_.YSpeed = 114;
							BYTE* raw = packPlayerMoving(&data_, 56);
							raw[3] = 114;
							double rotation = -4.13;
							memcpy(raw + 40, &rotation, 4);
							send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
							delete[] raw;
						}
					}
					else { // zalia
						if (diff <= 1) { // surado
							{
								if (pInfo(currentPeer)->geiger_time + 2500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
									pInfo(currentPeer)->geiger_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
									pInfo(currentPeer)->geiger_x = -1, pInfo(currentPeer)->geiger_y = -1;
									{
										int c_ = -1;
										modify_inventory(currentPeer, 2204, c_);
										int c_2 = 1;
										if (modify_inventory(currentPeer, 2286, c_2) != 0) {
											string name_ = pInfo(currentPeer)->world;
											vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
											if (p != worlds.end()) {
												World* world_ = &worlds[p - worlds.begin()];
												WorldDrop drop_block_{};
												drop_block_.id = 2286, drop_block_.count = 1, drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = pInfo(currentPeer)->x + rand() % 17, drop_block_.y = pInfo(currentPeer)->y + rand() % 17;
												dropas_(world_, drop_block_);
											}
										}
										PlayMods give_playmod{};
										give_playmod.id = 10;
										give_playmod.time = time(nullptr) + (thedaytoday == 3 ? 600 : 900);
										pInfo(currentPeer)->playmods.push_back(give_playmod);
										pInfo(currentPeer)->hand = 2286;
										update_clothes(currentPeer);
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert(a + "You are aglow with radiation! (`$Irradiated`` mod added, `$" + (thedaytoday == 3 ? "10" : "15") + " mins`` left)");
										p.CreatePacket(currentPeer);
										packet_(currentPeer, "action|play_sfx\nfile|audio/dialog_confirm.wav\ndelayMS|0");
									}
									int chanced = 0;
									if (thedaytoday == 3) chanced = 3;
									add_geiger_xp(currentPeer, 1);
									vector<int> geiger_items = { 2242,2244,2246,2248,2250,242,1796 };
									vector<int> rare_cr = { 13108,13106,12638,12406,12996,12640 };
									vector<int> rarest = { 4654 , 9380 , 11562, 1486 };
									int item_ = geiger_items[rand() % geiger_items.size()];
									if (rand() % 50 < 10 + chanced) item_ = rare_cr[rand() % rare_cr.size()];
									if (rand() % 50 < 2 + chanced) item_ = rarest[rand() % rarest.size()];
									int c_ = 1;
									if (modify_inventory(currentPeer, item_, c_) != 0) {
										string name_ = pInfo(currentPeer)->world;
										vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
										if (p != worlds.end()) {
											World* world_ = &worlds[p - worlds.begin()];
											WorldDrop drop_block_{};
											drop_block_.id = item_, drop_block_.count = 1, drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = pInfo(currentPeer)->x + rand() % 17, drop_block_.y = pInfo(currentPeer)->y + rand() % 17;
											dropas_(world_, drop_block_);
										}
									}
									gamepacket_t p;
									p.Insert("OnParticleEffect");
									p.Insert(48);
									p.Insert((float)pInfo(currentPeer)->x + 10, (float)pInfo(currentPeer)->y + 16);
									p.CreatePacket(currentPeer);
									{
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(currentPeer)->netID);
										p.Insert("I found `21 " + items[item_].name + "``!");
										p.Insert(0);
										p.CreatePacket(currentPeer);
										gamepacket_t p2;
										p2.Insert("OnConsoleMessage");
										p2.Insert(pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "`` found `21 " + items[item_].name + "``!");
										PlayerMoving data_{};
										data_.packetType = 19, data_.plantingTree = 0, data_.netID = 0;
										data_.punchX = item_;
										data_.x = pInfo(currentPeer)->x + 10, data_.y = pInfo(currentPeer)->y + 16;
										int32_t to_netid = pInfo(currentPeer)->netID;
										BYTE* raw = packPlayerMoving(&data_);
										raw[3] = 5;
										memcpy(raw + 8, &to_netid, 4);
										for (ENetPeer* currentPeer2 = server->peers; currentPeer2 < &server->peers[server->peerCount]; ++currentPeer2) {
											if (currentPeer2->state != ENET_PEER_STATE_CONNECTED or currentPeer2->data == NULL) continue;
											if (pInfo(currentPeer2)->world == pInfo(currentPeer)->world) {
												send_raw(currentPeer2, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												p2.CreatePacket(currentPeer2);
											}
										}
										delete[]raw;
									}
								}
							}
						}
						else {
							int t_ = 0;
							if (diff >= 6) t_ = 1350;
							else t_ = 1000;
							if (pInfo(currentPeer)->geiger_time + t_ < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
								pInfo(currentPeer)->geiger_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
								PlayerMoving data_{};
								data_.packetType = 17, data_.x = pInfo(currentPeer)->x + 10, data_.y = pInfo(currentPeer)->y + 16, data_.characterState = 0x8;
								data_.XSpeed = 2, data_.YSpeed = 114;
								BYTE* raw = packPlayerMoving(&data_, 56);
								raw[3] = 114;
								double rotation = -4.13;
								memcpy(raw + 40, &rotation, 4);
								send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
								delete[] raw;
							}
						}
					}
				}
			}
			long long time_ = time(nullptr);
			try {
				string name_ = pInfo(currentPeer)->world;
				vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
				if (p != worlds.end()) {
					World* world_ = &worlds[p - worlds.begin()];
					if (pInfo(currentPeer)->World_Timed - time_ == 60 && pInfo(currentPeer)->WorldTimed && pInfo(currentPeer)->tankIDName != world_->owner_name) {
						gamepacket_t p;
						p.Insert("OnTalkBubble"); p.Insert(pInfo(currentPeer)->netID); p.Insert("Your access to this world will expire in less than a minute!"); p.Insert(0); p.Insert(0); p.CreatePacket(currentPeer);
					}
					if (pInfo(currentPeer)->World_Timed - time_ < 0 && pInfo(currentPeer)->WorldTimed && pInfo(currentPeer)->tankIDName != world_->owner_name) {
						exit_(currentPeer);
					}
				}
			}
			catch (out_of_range) {
				cout << "Server error invalid (out of range) on remove access" << endl;
				return;
			}
			for (int i_ = 0; i_ < pInfo(currentPeer)->playmods.size(); i_++) {
				if (pInfo(currentPeer)->playmods[i_].id == 12) {
					if (pInfo(currentPeer)->valentine_time + 2500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						pInfo(currentPeer)->valentine_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						for (ENetPeer* valentine = server->peers; valentine < &server->peers[server->peerCount]; ++valentine) {
							if (valentine->state != ENET_PEER_STATE_CONNECTED or valentine->data == NULL) continue;
							if (pInfo(valentine)->world == pInfo(currentPeer)->world and pInfo(valentine)->tankIDName == pInfo(currentPeer)->playmods[i_].user) {
								if (not pInfo(valentine)->invis and not pInfo(currentPeer)->invis and pInfo(currentPeer)->x != -1 and pInfo(currentPeer)->y != -1 and pInfo(valentine)->x != -1 and pInfo(valentine)->y != -1) {
									gamepacket_t p;
									p.Insert("OnParticleEffect");
									p.Insert(13);
									p.Insert((float)pInfo(valentine)->x + 10, (float)pInfo(valentine)->y + 16);
									p.Insert((float)0), p.Insert((float)pInfo(currentPeer)->netID);
									bool double_send = false;
									for (int i_2 = 0; i_2 < pInfo(valentine)->playmods.size(); i_2++) {
										if (pInfo(valentine)->playmods[i_2].id == 12 and pInfo(valentine)->playmods[i_2].user == pInfo(currentPeer)->tankIDName) {
											double_send = true;
											break;
										}
									}
									gamepacket_t p2;
									p2.Insert("OnParticleEffect");
									p2.Insert(13);
									p2.Insert((float)pInfo(currentPeer)->x + 10, (float)pInfo(currentPeer)->y + 16);
									p2.Insert((float)0), p2.Insert((float)pInfo(valentine)->netID);
									for (ENetPeer* valentine_bc = server->peers; valentine_bc < &server->peers[server->peerCount]; ++valentine_bc) {
										if (valentine_bc->state != ENET_PEER_STATE_CONNECTED or valentine_bc->data == NULL) continue;
										if (pInfo(valentine_bc)->world == pInfo(currentPeer)->world) {
											p.CreatePacket(valentine_bc);
											if (double_send) p2.CreatePacket(valentine_bc);
										}
									}
								}
								break;
							}
						}
					}
				}
				if (pInfo(currentPeer)->playmods[i_].time - time_ < 0) {
					for (vector<string> get_ : info_about_playmods) {
						uint32_t playmod_id = atoi(get_[0].c_str());
						if (playmod_id == pInfo(currentPeer)->playmods[i_].id) {
							string playmod_name = get_[2];
							string playmod_on_remove = get_[4];
							pInfo(currentPeer)->playmods.erase(pInfo(currentPeer)->playmods.begin() + i_);
							packet_(currentPeer, "action|play_sfx\nfile|audio/dialog_confirm.wav\ndelayMS|0");
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert(playmod_on_remove + " (`$" + playmod_name + "`` mod removed)");
							p.CreatePacket(currentPeer);
							update_clothes(currentPeer);
							break;
						}
					}
				}
			}
		}
	}
}
int main(int argc, char* argv[]) {
	//system("COLOR B");
	//system("TITLE Grownet Private Server");
	//system("Setting up server...");
	//
	if (atexit(save_all)) {
		system("TITLE Private Server");
	}
	srand(unsigned int(time(nullptr)));
	signal(SIGINT, save_w), signal(SIGABRT, save_w);
	SetConsoleCtrlHandler(HandlerRoutine, true);
	//system("Serializing guild & server data...");
	system("COLOR A");
	system("TITLE ITSKYY STORE");
	cout << "ENet Server" << endl;
	cout << "Loading saved guild data" << endl;
	for (const auto& entry : fs::directory_iterator("database/guilds")) {
		if (!fs::is_directory(entry.path())) {
			string guild_id = explode(".", entry.path().filename().string())[0];
			json guild_read;
			ifstream read_guild(entry.path(), ifstream::binary);
			read_guild >> guild_read;
			read_guild.close();
			Guild new_guild{};
			new_guild.guild_id = atoi(guild_id.c_str());
			new_guild.guild_name = guild_read["guild_name"].get<string>();
			new_guild.guild_description = guild_read["guild_description"].get<string>();
			new_guild.guild_mascot = guild_read["guild_mascot"].get<vector<uint16_t>>();
			new_guild.guild_level = guild_read["guild_level"].get<uint16_t>();
			new_guild.guild_xp = guild_read["guild_xp"].get<uint32_t>();
			new_guild.coleader_access = guild_read["coleader_access"].get<bool>();
			new_guild.coleader_elder_access = guild_read["coleader_elder_access"].get<bool>();
			new_guild.all_access = guild_read["all_access"].get<bool>();
			new_guild.guild_world = guild_read["guild_world"].get<string>();
			json a_ = guild_read["guild_members"].get<json>();
			for (int i_ = 0; i_ < a_.size(); i_++) {
				GuildMember new_member{};
				new_member.member_name = a_[i_]["member_name"].get<string>();
				new_member.role_id = a_[i_]["role_id"].get<int>();
				new_member.public_location = a_[i_]["public_location"].get<bool>();
				new_member.show_notifications = a_[i_]["show_notifications"].get<bool>();
				new_member.last_online = a_[i_]["last_online"].get<long long>();
				new_guild.guild_members.push_back(new_member);
			}
			json b_ = guild_read["guild_logs"].get<json>();
			for (int i_ = 0; i_ < b_.size(); i_++) {
				GuildLog new_log{};
				new_log.info = b_[i_]["info"].get<string>();
				new_log.display_id = b_[i_]["display_id"].get<uint16_t>();
				new_log.date = b_[i_]["date"].get<long long>();
				new_guild.guild_logs.push_back(new_log);
			}
			guilds.push_back(new_guild);
		}
	}
	bool itscrime = false;
	ifstream lol("disini_setting_server.json");
	if (!lol.is_open()) {
		cout << "enter server port : ";
		cin >> server_port;
		cout << "enter server name : ";
		cin >> server_name;
		cout << "enter creator name  : ";
		cin >> creator1;
		cout << "Osm Www/Kayak www.growtopia1.com : ";
		cin >> osm_link;
		cout << "Osm Cache/Kayak cache/ : ";
		cin >> osm_path;
		ofstream le("disini_setting_server.json");
		json j;
		j["port"] = server_port;
		j["name"] = server_name;
		j["creator1"] = creator1;
		j["creator4"] = creator4;
		j["creator5"] = creator5;
		j["creator6"] = creator6;
		j["creator7"] = creator7;
		j["creator8"] = creator8;
		j["creator9"] = creator9;
		j["creator10"] = creator10;
		j["creator11"] = creator11;
		j["creator12"] = creator12;
		j["Onsupermain"] = osm_link;
		j["CdnCache"] = osm_path;
		j["Proto"] = proto;
		le << j;
		le.close();
	}
	json j;
	lol >> j;
	lol.close();
	server_port = j["port"].get<int>();
	server_name = j["name"].get<string>();
	creator1 = j["creator1"].get<string>();
	creator4 = j["creator4"].get<string>();
	creator5 = j["creator5"].get<string>();
	creator6 = j["creator6"].get<string>();
	creator7 = j["creator7"].get<string>();
	creator8 = j["creator8"].get<string>();
	creator9 = j["creator9"].get<string>();
	creator10 = j["creator10"].get<string>();
	creator11 = j["creator11"].get<string>();
	creator12 = j["creator12"].get<string>();
	osm_link = j["Onsupermain"].get<string>();
	osm_path = j["CdnCache"].get<string>();
	proto = j["Proto"].get<string>();
	if (atexit(trigger_save_))
		cout << "Saving...\n";

	if (items_dat() == -1)
		cout << "items.dat klaida maybe missing or moved" << endl;
	else {
		cout << setGems(items.size()) << " items loaded" << endl;
	}
	server_port = 17091;
	if (init_enet(server_port) == -1) //17099
		cout << "enet klaida or already listen on port 17091" << endl;
	else
	system("CLS");
	cout << ".####.########..######..##....##.##....##.##....##.....######..########..#######..########..########" << endl;
	cout << "..##.....##....##....##.##...##...##..##...##..##.....##....##....##....##.....##.##.....##.##......" << endl;
	cout << "..##.....##....##.......##..##.....####.....####......##..........##....##.....##.##.....##.##......" << endl;
	cout << "..##.....##.....######..#####.......##.......##........######.....##....##.....##.########..######.." << endl;
	cout << "..##.....##..........##.##..##......##.......##.............##....##....##.....##.##...##...##......" << endl;
	cout << "..##.....##....##....##.##...##.....##.......##.......##....##....##....##.....##.##....##..##......" << endl;
	cout << ".####....##.....######..##....##....##.......##........######.....##.....#######..##.....##.########" << endl;
	system("CLS");
	cout << "Name Server : " << server_name << endl;
	cout << "Listening Port : " << server_port << endl;
	cout << "OnsuperMain : " << osm_link << endl;
	cout << "CDN : " << osm_path << endl;
	cout << "Proto : " << proto << endl;
	cout << "OWNER SERVER UTAMA" << endl;
	cout << "creator 1 : " << creator1 << endl;
	cout << "NOTE : creator YANG DI BAWAH BISA DI JUAL" << endl;
	cout << "creator 2 : " << creator4 << endl;
	cout << "creator 3 : " << creator5 << endl;
	cout << "creator 4 : " << creator6 << endl;
	cout << "creator 5 : " << creator7 << endl;
	cout << "creator 6 : " << creator8 << endl;
	cout << "creator 7 : " << creator9 << endl;
	cout << "creator 8 : " << creator10 << endl;
	cout << "creator 9 : " << creator11 << endl;
	cout << "creator 10 : " << creator12 << endl;
	system("CLS");
	cout << ".####.########..######..##....##.##....##.##....##.....######..########..#######..########..########" << endl;
	cout << "..##.....##....##....##.##...##...##..##...##..##.....##....##....##....##.....##.##.....##.##......" << endl;
	cout << "..##.....##....##.......##..##.....####.....####......##..........##....##.....##.##.....##.##......" << endl;
	cout << "..##.....##.....######..#####.......##.......##........######.....##....##.....##.########..######.." << endl;
	cout << "..##.....##..........##.##..##......##.......##.............##....##....##.....##.##...##...##......" << endl;
	cout << "..##.....##....##....##.##...##.....##.......##.......##....##....##....##.....##.##....##..##......" << endl;
	cout << ".####....##.....######..##....##....##.......##........######.....##.....#######..##.....##.########" << endl;
	cout << "" << endl;
	cout << "" << endl;
	cout << "Server Up! Current time: " + currentDateTime() + "" << endl;
	cout << "Items loaded: " << setGems(items.size()) << endl;
	cout << "===> NEW UPDATE V30 CPP <===" << endl;
	cout << "===> Remake By ItsKyy#7628 <===" << endl;
	cout << "==> Always Update" << endl;
	cout << "==> Dont Leak This CPP !!" << endl;
	cout << "==> Found Bug? Contact : +62878-2005-6972 <==" << endl;
	cout << "" << endl;
	system("COLOR 2");
	std::thread runautosave(autosave);
	if (runautosave.joinable()) {
		runautosave.detach();
	}
	daily_quest();
	thread a__(biar_jalan);
	a__.detach();
	thread spammer(loop_spammer);
	spammer.detach();
	{
		ifstream ifs("database/server_events.json");
		if (ifs.is_open()) {
			json j;
			ifs >> j;
			top_basher = (!(j.find("2") != j.end()) ? top_basher : j["2"].get<vector<pair<int, string>>>());
			top_basher_winners = (!(j.find("3") != j.end()) ? top_basher_winners : j["3"].get<vector<pair<int, string>>>());
			top_old_winners = (!(j.find("4") != j.end()) ? top_old_winners : j["4"].get<string>());
			ridbans = (!(j.find("rid") != j.end()) ? ridbans : j["rid"].get<vector<string>>());
			top_points = (!(j.find("h" + to_string(today_day)) != j.end()) ? top_points : j["h" + to_string(today_day)].get<vector<pair<int, string>>>());
			top_yesterday = (!(j.find("h" + to_string(today_day - 1)) != j.end()) ? top_yesterday : j["h" + to_string(today_day - 1)].get<vector<pair<int, string>>>());
			top_overall = (!(j.find("m" + to_string(today_month)) != j.end()) ? top_overall : j["m" + to_string(today_month)].get<vector<pair<int, string>>>());
		}
	}
	honors_reset();
	/*ifstream ifs("db/volcanic_capes.json");
	if (ifs.is_open()) {
		json j;
		ifs >> j;
		volcanic_cape = j["v1"].get<int>();
		volcanic_wings = j["v2"].get<int>();
		if (today_day != j["v3"].get<int>()) {
			volcanic_cape = 0;
			volcanic_wings = 0;
		}
	}*/
	// {
	{
	ifstream ifs("database/rich_player.json");
	if (ifs.is_open()) {
		json j;
		ifs >> j;
		vector<pair<long long int, string>> richPlayer = j["list"];
		top_richest = richPlayer;
	}
	ifs.close();
	}
		ifstream ifs("db/news.json");
		if (ifs.is_open()) {
			json j;
			ifs >> j;
			news_text = j["news"].get<string>();
		}
	// }
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	thedaytoday = newtime.tm_wday;
	{
		const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		string month = months[newtime.tm_mon], translated = "", str = to_string(today_day), locke = "";
		if (str == "01" || str == "21") translated = "st";
		else if (str == "02" || str == "22") translated = "nd";
		else if (str == "03") translated = "rd";
		else translated = "th";
		if (thedaytoday == 5 or thedaytoday == 6 or thedaytoday == 0 or thedaytoday == 1) locke = "\nadd_spacer|small|\nadd_textbox|`oToday Growtopia is being paid a visit by `5Locke`` the traveling salesman! He comes one day a month to hawk his fabulous wares, though this time he'll stick around a day and a half to introduce himself. Checkout the world `5LOCKETOWN``!``|left|";
		news_texture = "set_default_color|`o\nadd_label_with_icon|big|" + server_name + "`w Gazette``|left|5016|\nadd_spacer|small|\nadd_image_button||interface/large/news_banner.rttex|bannerlayout|||\nadd_spacer|small|\nadd_textbox|`w" + month + " " + to_string(today_day) + "" + translated + ": ```25 Juni Update - Gems 3x!``|left|\nadd_spacer|small|\nadd_image_button|iotm_layout|interface/large/gazette/gazette_3columns_feature_btn04.rttex|3imageslayout|||\nadd_image_button|iotm_layout|interface/large/gazette/gazette_3columns_feature_btn03.rttex|3imageslayout|||\nadd_image_button|iotm_layout|interface/large/gazette/gazette_3columns_feature_btn10.rttex|3imageslayout|||" + locke + news_text + "\nadd_quick_exit|";
	}
	if (thedaytoday == 1) theitemtoday = 5040;
	else if (thedaytoday == 2) theitemtoday = 5042;
	else if (thedaytoday == 3) theitemtoday = 5044;
	else if (thedaytoday == 4) theitemtoday = 5032;
	else if (thedaytoday == 5)theitemtoday = 5034;
	else if (thedaytoday == 6) theitemtoday = 5036;
	else if (thedaytoday == 0)theitemtoday = 5038;
	ENetEvent event;
	while (true) {
		while (enet_host_service(server, &event, 1000) > 0) {
			ENetPeer* peer = event.peer;
			switch (event.type) {
				case ENET_EVENT_TYPE_CONNECT:
				{
					char clientConnection[16];
					enet_address_get_host_ip(&peer->address, clientConnection, 16);
					send_(peer, 1, nullptr, 0);
					gamepacket_t p;
					p.Insert("OnConsoleMessage");
					//p.Insert("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");			
					p.Insert("`2Connected to `0" + server_name + " !``");
					p.Insert("");
					p.CreatePacket(peer);
					peer->data = new Player;
					pInfo(peer)->id = peer->connectID, pInfo(peer)->ip = clientConnection;
					string error = "";
					int logged = 0;
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(peer)->ip != pInfo(currentPeer)->ip) continue;
						logged++;
					}
					if (logged > 4) error = "`4OOPS:`` Too many people logging in at once. Please press `5CANCEL`` and try again in a few seconds.";
					//for (int i = 0; i < ipbans.size(); i++) if (pInfo(peer)->ip == ipbans[i]) error = "action|log\nmsg|CT:[S]_ `4Sorry, you are not allowed to enter the game from this location. Contact `5Discord Staff Team `4if you have any questions.";
					if (pInfo(peer)->ip != pInfo(peer)->meta and pInfo(peer)->meta != "") error = "action|log\nmsg|CT:[S]_ `4Can not make new account!`` Sorry, but IP " + pInfo(peer)->ip + " is not permitted to create NEW Growtopia accounts at this time. (This can be because there is an open proxy/VPN here or abuse has from this IP) Please try again from another IP address.";
					//if (pInfo(peer)->gameVersion != "4,17") error = "action|log\nmsg|CT:[S]_ `5Update Required: `oNow version Growtopia is 4,17, Please update your growtopia.";
					if (error != "") packet_(peer, error, ""), enet_peer_disconnect_later(peer, 0);
					
					break;
				}
				case ENET_EVENT_TYPE_RECEIVE:
				{
					loop_worlds();
					switch (message_(event.packet)) {
					case 2:
					{
						string cch = text_(event.packet);
						if (cch.size() > 1024) break;
						if (cch == "action|getDRAnimations\n" || cch == "action|refresh_player_tribute_data\n") break;
						if (pInfo(peer)->lpps + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
							pInfo(peer)->pps = 0;
							pInfo(peer)->lpps = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						}
						else {
							pInfo(peer)->pps++;
							if (pInfo(peer)->pps >= 10) {
								enet_peer_disconnect_later(peer, 0);
								break;
							}
						}
						if (pInfo(peer)->requestedName.empty()) {
							if (pInfo(peer)->enter_game != 0 || pInfo(peer)->world != "") enet_peer_disconnect_later(peer, 0);
							else player_login(peer, cch);
						}
						add_packet_logs(" [" + pInfo(peer)->ip + "] (" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + " | World: " + pInfo(peer)->world == "" ? "EXIT" : pInfo(peer)->world + ") " + cch);
						if (pInfo(peer)->requestedName.empty()) {
							if (pInfo(peer)->enter_game != 0 || pInfo(peer)->world != "") {
								if (not pInfo(peer)->tankIDName.empty())
									if (pInfo(peer)->trading_with != -1) {
										cancel_trade(peer, false);
									}
								enet_peer_disconnect_later(peer, 0);
								save_player(pInfo(peer), false);
								delete peer->data;
								peer->data = NULL;
							}
							else player_login(peer, cch);
						}
					else if (cch.find("action|input") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 4) break;
							string msg = explode("\n", t_[3])[0];
							if (pInfo(peer)->tankIDName == "") break;
							if (msg.length() <= 0 || msg.length() > 120 || msg.empty() || std::all_of(msg.begin(), msg.end(), [](char c) {return std::isspace(c); })) continue;
							for (char c : msg) if (c < 0x20 || c>0x7A) continue;
							space_(msg);
							if (msg[0] == '/') SendCmd(peer, msg);
							else {
								if (msg[0] == '`' and msg.size() <= 2) break;
								if (pInfo(peer)->world == "") break;
								if (pInfo(peer)->tut_sb == false) tutorial_(peer, "tut_sb");
								if (has_playmod(pInfo(peer), "duct tape") || has_playmod(pInfo(peer), "KONTOL")) {
									string msg2 = "";
									for (int i = 0; i < msg.length(); i++) {
										if (isspace(msg[i])) msg2 += " ";
										else {
											if (isupper(msg[i])) msg2 += i % 2 == 0 ? "KON" : "TOL";
											else msg2 += i % 2 == 0 ? "kon" : "tol";
										}
									}
									msg = msg2;
								}
								string check_ = msg;
								transform(check_.begin(), check_.end(), check_.begin(), ::tolower);
								{
									string name_ = pInfo(peer)->world;
									vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									if (p != worlds.end()) {
										World* world_ = &worlds[p - worlds.begin()];
										if (world_->silence and pInfo(peer)->superdev != 1 and world_->owner_name != pInfo(peer)->tankIDName and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end()) {
											gamepacket_t p;
											p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("`1(Peasants must not speak)"), p.Insert(1), p.CreatePacket(peer);
											break;
										}
									}
								}
								bool warned = false;
								pInfo(peer)->not_same++;
								if (pInfo(peer)->last_input_text == msg) pInfo(peer)->same_input++;
								pInfo(peer)->last_input_text = msg;
								if (pInfo(peer)->last_spam_detection + 100 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) pInfo(peer)->last_spam_detection = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count(), pInfo(peer)->same_input = 0, pInfo(peer)->not_same = 0;
								if (pInfo(peer)->same_input >= 3 || pInfo(peer)->not_same >= 5) {
									gamepacket_t p;
									p.Insert("OnConsoleMessage"), p.Insert("`6>>`4Spam detected! ``Please wait a bit before typing anything else.  Please note, any form of bot/macro/auto-paste will get all your accounts banned, so don't do it!"), p.CreatePacket(peer);
								}
								else {
									gamepacket_t p, p2;
									p.Insert("OnConsoleMessage");
									p.Insert("CP:_PL:0_OID:_CT:[W]_ `6<`w" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "`6> `$" + (has_playmod(pInfo(peer), "Infected!") ? "`2" : "") + "" + ((pInfo(peer)->superdev == 1 and pInfo(peer)->d_name.empty()) ? "`5" : (pInfo(peer)->dev == 1 and pInfo(peer)->d_name.empty()) ? "`1" : (pInfo(peer)->tmod == 1 and pInfo(peer)->d_name.empty()) ? "`^" : "`$") + msg + "`````");
									p2.Insert("OnTalkBubble");
									p2.Insert(pInfo(peer)->netID);
									if (check_ != ":/" and check_ != ":p" and check_ != ":*" and check_ != ";)" and check_ != ":d" and check_ != ":o" and check_ != ":'(" and check_ != ":(") {
										p2.Insert("CP:_PL:0_OID:_player_chat=" + a + ((pInfo(peer)->owner == 1 and pInfo(peer)->d_name.empty()) ? own_chat : (pInfo(peer)->superdev == 1 and pInfo(peer)->d_name.empty()) ? smod_chat : (pInfo(peer)->dev == 1 and pInfo(peer)->d_name.empty()) ? royal_chat : (pInfo(peer)->vip == 1 and pInfo(peer)->d_name.empty()) ? vip_chat : ((pInfo(peer)->tmod == 1 and pInfo(peer)->d_name.empty())) ? "`^" : "`0") + msg);
									}
									else p2.Insert(msg);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == pInfo(peer)->world) {
											bool muted_ = false;
											for (int c_ = 0; c_ < pInfo(currentPeer)->friends.size(); c_++) {
												if (pInfo(currentPeer)->friends[c_].name == pInfo(peer)->tankIDName) {
													if (pInfo(currentPeer)->friends[c_].mute) {
														muted_ = true;
														break;
													}
												}
											} if (not muted_ and not pInfo(currentPeer)->Cheat_HideChat) {
												p.CreatePacket(currentPeer);
												p2.CreatePacket(currentPeer);
											}
										}
									}
								}
							}
							break;
						}
						else if (cch.find("action|mod_trade") != string::npos or cch.find("action|rem_trade") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 3) break;
							int item_id = atoi(explode("\n", t_[2])[0].c_str()), c_ = 0;
							modify_inventory(peer, item_id, c_);
							if (c_ == 0) break;
							if (c_ == 1 or cch.find("action|rem_trade") != string::npos) {
								mod_trade(peer, item_id, c_, (cch.find("action|rem_trade") != string::npos ? true : false));
								break;
							}
							if (cch.find("action|rem_trade") == string::npos) {
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`2Trade`` `w" + items[item_id].name + "``|left|" + to_string(item_id) + "|\nadd_textbox|`2Trade how many?``|left|\nadd_text_input|count||" + to_string(c_) + "|5|\nembed_data|itemID|" + to_string(item_id) + "\nend_dialog|trade_item|Cancel|OK|");
								p.CreatePacket(peer);
							}
							break;
						}
						else if (cch.find("action|trade_accept") != string::npos) {
							if (pInfo(peer)->trading_with != -1) {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 3) break;
								string status_ = explode("\n", t_[2])[0];
								if (status_ != "1" and status_ != "0") break;
								bool f_ = false;
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (pInfo(currentPeer)->world == pInfo(peer)->world) {
										if (pInfo(currentPeer)->netID == pInfo(peer)->trading_with and pInfo(peer)->netID == pInfo(currentPeer)->trading_with) {
											string name_ = pInfo(peer)->world;
											vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
											if (p != worlds.end()) {
												World* world_ = &worlds[p - worlds.begin()];
												if (status_ == "1")
													pInfo(peer)->trade_accept = 1;
												else
													pInfo(peer)->trade_accept = 0;
												if (pInfo(peer)->trade_accept and pInfo(currentPeer)->trade_accept) {
													// check inv space   
													if (not trade_space_check(peer, currentPeer)) {
														pInfo(peer)->trade_accept = 0, pInfo(currentPeer)->trade_accept = 0;
														gamepacket_t p;
														p.Insert("OnTradeStatus");
														p.Insert(pInfo(peer)->netID);
														p.Insert("");
														p.Insert("`o" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "``'s offer.``");
														p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\naccepted|0");
														p.CreatePacket(peer);
														{
															gamepacket_t p;
															p.Insert("OnTradeStatus");
															p.Insert(pInfo(peer)->netID);
															p.Insert("");
															p.Insert("`o" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "``'s offer.``");
															p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\nreset_locks|1\naccepted|0");
															p.CreatePacket(currentPeer);
														}
														f_ = true;
														break;
													}
													else if (not trade_space_check(currentPeer, peer)) {
														pInfo(peer)->trade_accept = 0, pInfo(currentPeer)->trade_accept = 0;
														gamepacket_t p;
														p.Insert("OnTradeStatus");
														p.Insert(pInfo(currentPeer)->netID);
														p.Insert("");
														p.Insert("`o" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + "``'s offer.``");
														p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\naccepted|0");
														p.CreatePacket(currentPeer);
														{
															gamepacket_t p;
															p.Insert("OnTradeStatus");
															p.Insert(pInfo(currentPeer)->netID);
															p.Insert("");
															p.Insert("`o" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + "``'s offer.``");
															p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\nreset_locks|1\naccepted|0");
															p.CreatePacket(peer);
														}
														f_ = true;
														break;
													}
													{
														gamepacket_t p;
														p.Insert("OnForceTradeEnd");
														p.CreatePacket(peer);
													}
													send_trade_confirm_dialog(peer, currentPeer);
													break;
												}
												gamepacket_t p;
												p.Insert("OnTradeStatus");
												p.Insert(pInfo(peer)->netID);
												p.Insert("");
												p.Insert("`o" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "``'s offer.``");
												p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\naccepted|" + status_);
												p.CreatePacket(peer);
												{
													{
														gamepacket_t p;
														p.Insert("OnTradeStatus");
														p.Insert(pInfo(currentPeer)->netID);
														p.Insert("");
														p.Insert("`o" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + "``'s offer.``");
														p.Insert("locked|0\nreset_locks|1\naccepted|0");
														p.CreatePacket(currentPeer);
													}
													gamepacket_t p;
													p.Insert("OnTradeStatus");
													p.Insert(pInfo(currentPeer)->netID);
													p.Insert("");
													p.Insert("`o" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + "``'s offer.``");
													p.Insert("locked|0\naccepted|1");
													p.CreatePacket(currentPeer);
													{
														gamepacket_t p;
														p.Insert("OnTradeStatus");
														p.Insert(pInfo(currentPeer)->netID);
														p.Insert("");
														p.Insert("`o" + (not pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->d_name : pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName) + "``'s offer.``");
														p.Insert(make_trade_offer(pInfo(currentPeer), true) + "locked|0\nreset_locks|1\naccepted|0");
														p.CreatePacket(currentPeer);
													}
													{
														gamepacket_t p;
														p.Insert("OnTradeStatus");
														p.Insert(pInfo(peer)->netID);
														p.Insert("");
														p.Insert("`o" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "``'s offer.``");
														p.Insert(make_trade_offer(pInfo(peer), true) + "locked|0\nreset_locks|1\naccepted|" + status_);
														p.CreatePacket(currentPeer);
													}
												}
											}
											f_ = true;
											break;
										}
									}
								} if (not f_) {
									if (status_ == "1")
										pInfo(peer)->trade_accept = 1;
									else
										pInfo(peer)->trade_accept = 0;
								}
							}
							break;
						}
						if (cch.find("action|dialog_return\ndialog_name|game_slot") != string::npos) {
							if (cch.find("buttonClicked|playagain") != string::npos) {
								srand((unsigned)time(NULL));
								int count = atoi(explode("\n", explode("bet_slot|", cch)[1])[0].c_str());
								int xas = rand() % 8 + 1;
								int got = 0;
								got = pInfo(peer)->bankfixd;
								
								if (count < 0 or count > got) goto menu_slot;
								else if (got < 0 or got < count) goto menu_slot;
								else if (got == 0 or count == 0) goto menu_slot;
								else if (count > 10) goto menu_slot;
								else {
									if (xas == 1 or xas == 3 or xas == 5 or xas == 7) {
										if (got > 100000) goto menu_slot;
										if (got == 0) goto menu_slot;
										int gota = 0;
										gota = count * 2;
										pInfo(peer)->bankfixd += gota;
										DialogBuilder dialog;
										dialog.add_image_button("", "slot_win.rttex", "OPENDIALOG", "")
											.add_smalltext(format("`2Nice to see you back`` {}``, <CR>`0To play this game you need `cBgl(Blue Gem Lock)`` which is in the bank and make sure you have more than 1 Bgl!", pInfo(peer)->name_color + pInfo(peer)->tankIDName))
											.add_smalltext("`5Please remember! `0If you `4lose`0, you will lose your Bgl to how many Bet you placed and If you `2win`0, you will get back Bgl 2X according to how many Bet you placed!")
											.add_spacer(false)
											.add_label_icon(false, 7188, format("`$You have : `3{}`` in the bank.", setGems(pInfo(peer)->bankfixd)))
											.add_label_icon(false, 7188, format("`$You win (`2+x{} Bgl``) from placing a bet (`9{}``)", fixint(gota), std::to_string(count)))
											.add_textbox("`2Playing!``")
											.add_text_input(3, "bet_slot", "`0Put your bet:``", "1")
											.add_static_icon_button("playagain", 758, "`2Playing Game", "`2Playing Game``")
											.end_list()
											//.add_smalltext("`0Good luck!``")
											.add_spacer(false)
											.end_dialog("game_slot", "Cancel", "");
										enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(dialog.to_string()).pack());
										packet_(peer, "action|play_sfx\nfile|audio/slot_win.wav\ndelayMS|0");
									}
									else if (xas == 2 or xas == 4 or xas == 6 or xas == 8 or xas == 5) {
										if (got == 0) goto menu_slot;
										int lose = count * 2;
										pInfo(peer)->bankfixd -= lose;
										DialogBuilder dialog;
										dialog.add_image_button("", "slot_lose.rttex", "OPENDIALOG", "")
											.add_smalltext(format("`2Nice to see you back`` {}``, <CR>`0To play this game you need `cBgl(Blue Gem Lock)`` which is in the bank and make sure you have more than 1 Bgl!", pInfo(peer)->name_color + pInfo(peer)->tankIDName))
											.add_smalltext("`5Please remember! `0If you `4lose`0, you will lose your Bgl to how many Bet you placed and If you `2win`0, you will get back Bgl 2X according to how many Bet you placed!")
											.add_spacer(false)
											.add_label_icon(false, 7188, format("`$You have : `3{}`` in the bank.", setGems(pInfo(peer)->bankfixd)))
											.add_label_icon(false, 7188, format("`$You lose (`4-x{}``) from placing a bet (`9{}``)", fixint(lose), std::to_string(count)))
											.add_textbox("`2Playing!``")
											.add_text_input(3, "bet_slot", "`0Put your bet:``", "1")
											.add_static_icon_button("playagain", 758, "`2Playing Game", "`2Playing Game``")
											.end_list()
											//.add_smalltext("`0Good luck!``")
											.add_spacer(false)
											.end_dialog("game_slot", "Cancel", "");
										enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(dialog.to_string()).pack());
										packet_(peer, "action|play_sfx\nfile|audio/slot_lose.wav\ndelayMS|0");
									}
								}
								menu_slot:
								DialogBuilder fail;
								fail.add_image_button("", "slot_banner.rttex", "OPENDIALOG", "")
									.add_smalltext(format("`2Nice to see you back`` {}``, <CR>`0To play this game you need `cBgl(Blue Gem Lock)`` which is in the bank and make sure you have more than 1 Bgl!", pInfo(peer)->name_color + pInfo(peer)->tankIDName))
									.add_smalltext("`5Please remember! `0If you `4lose`0, you will lose your Bgl to how many Bet you placed and If you `2win`0, you will get back Bgl 2X according to how many Bet you placed!")
									.add_spacer(false)
									.add_smalltext("`4Try Again! Please enter the correct number!")
									.add_label_icon(false, 7188, format("`$You have : `3{}`` in the bank.", setGems(pInfo(peer)->bankfixd)))
									.add_textbox("`2Playing!``")
									.add_text_input(3, "bet_slot", "`0Put your bet:``", "")
									.add_static_icon_button("playagain", 758, "`2Playing Game", "`2Playing Game``")
									.end_list()
									//.add_smalltext("`0Good luck!``")
									.add_spacer(false)
									.end_dialog("game_slot", "Cancel", "");
								enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(fail.to_string()).pack());
							}
							break;
						}
						if (cch.find("action|dialog_return\ndialog_name|kit_pass") != string::npos) {
							if (cch.find("buttonClicked|tab_1") != string::npos) kit_Pass(peer, true, "tab_1", 0);
							else if (cch.find("buttonClicked|tab_2") != string::npos) kit_Pass(peer, true, "tab_2", 0);
							//kit1
							else if (cch.find("buttonClicked|info_5480") != string::npos) {
								string pass = "";
								if (pInfo(peer)->Kit_Poin >= 499 && pInfo(peer)->claim_kit == false) pass += "\nadd_button|claim-5480|`wClaim Rewards``|noflags|0|0|";
								else  pass += "\nadd_button||`wRewards Locked``|off|0|0|";
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|\nadd_label_with_icon|small|Claim `3" + items[5480].ori_name + "`` |left|5480|"
									"\nadd_spacer|small|"
									"\nadd_textbox|`5" + items[5480].description + "`` from KitPass lvl 1 & `2500 points!``|left|"
									"\nadd_spacer|small|" + pass + "\nadd_spacer|small|\nadd_button|tab_1|`wBack to Menu``|noflags|0|0|\nend_dialog|kit_pass|||");
								p.CreatePacket(peer);
							}
							else if (cch.find("buttonClicked|claim-5480") != string::npos) {
								//int item = atoi(cch.substr(57, cch.length() - 57).c_str());
								if (pInfo(peer)->claim_kit == false) {
									int count = 1, itemID = 0;
									if (modify_inventory(peer, 5480, count) == 0) {
										pInfo(peer)->claim_kit = true;
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("Congratulations! You have received 1 `8" + items[5480].ori_name + "`` from KitPass Reward!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
										BYTE* raw = packPlayerMoving(&data_);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw;
										kit_Pass(peer, true, "tab_1", 0);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You have full inventory space!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
									}
								}
							}
							//kit2
							else if (cch.find("buttonClicked|info_12868") != string::npos) {
								string pass = "";
								if (pInfo(peer)->Kit_Poin >= 999 && pInfo(peer)->claim_kit1 == false) pass += "\nadd_button|claim-12868|`wClaim Rewards``|noflags|0|0|";
								else  pass += "\nadd_button||`wRewards Locked``|off|0|0|";
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|\nadd_label_with_icon|big|Claim `3" + items[12868].ori_name + "`` |left|12868|"
									"\nadd_spacer|small|"
									"\nadd_textbox|`wYou can claim `5" + items[12868].ori_name + "`` If Your KitPass lvl 2 & point `21000!``|left|"
									"\nadd_spacer|small|" + pass + "\nadd_spacer|small|\nadd_button|tab_1|`wBack to Menu``|noflags|0|0|\nend_dialog|kit_pass|||");
								p.CreatePacket(peer);
							}
							else if (cch.find("buttonClicked|claim-12868") != string::npos) {
								//int item = atoi(cch.substr(57, cch.length() - 57).c_str());
								if (pInfo(peer)->claim_kit1 == false) {
									int count = 1, itemID = 0;
									if (modify_inventory(peer, 12868, count) == 0) {//11118, 6312, 2592, 1782
										pInfo(peer)->claim_kit1 = true;
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("Congratulations! You have received 1 `8" + items[12868].ori_name + "`` from KitPass Reward!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
										BYTE* raw = packPlayerMoving(&data_);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw;
										kit_Pass(peer, true, "tab_1", 0);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You have full inventory space!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
									}
								}
							}
							//kit3
							else if (cch.find("buttonClicked|info_11118") != string::npos) {
								string pass = "";
								if (pInfo(peer)->Kit_Poin >= 1999 && pInfo(peer)->claim_kit2 == false) pass += "\nadd_button|claim-11118|`wClaim Rewards``|noflags|0|0|";
								else  pass += "\nadd_button||`wRewards Locked``|off|0|0|";
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|\nadd_label_with_icon|big|Claim `3" + items[11118].ori_name + "`` |left|11118|"
									"\nadd_spacer|small|"
									"\nadd_textbox|`wYou can claim `5" + items[11118].ori_name + "`` If Your KitPass lvl 3 & point `22000!``|left|"
									"\nadd_spacer|small|" + pass + "\nadd_spacer|small|\nadd_button|tab_1|`wBack to Menu``|noflags|0|0|\nend_dialog|kit_pass|||");
								p.CreatePacket(peer);
							}
							else if (cch.find("buttonClicked|claim-11118") != string::npos) {
								//int item = atoi(cch.substr(57, cch.length() - 57).c_str());  
								if (pInfo(peer)->claim_kit2 == false) {
									int count = 2, itemID = 0;
									if (modify_inventory(peer, 11118, count) == 0) {//, 6312, 2592, 1782
										pInfo(peer)->claim_kit2 = true;
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("Congratulations! You have received 1 `8" + items[11118].ori_name + "`` from KitPass Reward!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
										BYTE* raw = packPlayerMoving(&data_);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw;
										kit_Pass(peer, true, "tab_1", 0);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You have full inventory space!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
									}
								}
							}
							//kit4
							else if (cch.find("buttonClicked|info_6312") != string::npos) {
								string pass = "";
								if (pInfo(peer)->Kit_Poin >= 2999 && pInfo(peer)->claim_kit3 == false) pass += "\nadd_button|claim-6312|`wClaim Rewards``|noflags|0|0|";
								else  pass += "\nadd_button||`wRewards Locked``|off|0|0|";
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|\nadd_label_with_icon|big|Claim `3" + items[6312].ori_name + "`` |left|6312|"
									"\nadd_spacer|small|"
									"\nadd_textbox|`wYou can claim `5" + items[6312].ori_name + "`` If Your KitPass lvl 4 & point `23000!``|left|"
									"\nadd_spacer|small|" + pass + "\nadd_spacer|small|\nadd_button|tab_1|`wBack to Menu``|noflags|0|0|\nend_dialog|kit_pass|||");
								p.CreatePacket(peer);
							}
							else if (cch.find("buttonClicked|claim-6312") != string::npos) {
									//int item = atoi(cch.substr(57, cch.length() - 57).c_str());
									if (pInfo(peer)->claim_kit3 == false) {
										int count = 1, itemID = 0;
										if (modify_inventory(peer, 6312, count) == 0) {//, 2592, 1782
											pInfo(peer)->claim_kit3 = true;
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											{
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("Congratulations! You have received " + to_string(count) + " `8" + items[6312].ori_name + "`` from KitPass Reward!");
												p.Insert(0), p.Insert(0);
												p.CreatePacket(peer);
											}
											PlayerMoving data_{};
											data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
											BYTE* raw = packPlayerMoving(&data_);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw;
											kit_Pass(peer, true, "tab_1", 0);
										}
										else {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("You have full inventory space!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
									}
									}
							//kit5
							else if (cch.find("buttonClicked|info_2592") != string::npos) {
								string pass = "";
								if (pInfo(peer)->Kit_Poin >= 3999 && pInfo(peer)->claim_kit4 == false) pass += "\nadd_button|claim-2592|`wClaim Rewards``|noflags|0|0|";
								else  pass += "\nadd_button||`wRewards Locked``|off|0|0|";
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|\nadd_label_with_icon|big|Claim `3" + items[2592].ori_name + "`` |left|2592|"
									"\nadd_spacer|small|"
									"\nadd_textbox|`wYou can claim `5" + items[2592].ori_name + "`` If Your KitPass lvl 5 & point `24000!``|left|"
									"\nadd_spacer|small|" + pass + "\nadd_spacer|small|\nadd_button|tab_1|`wBack to Menu``|noflags|0|0|\nend_dialog|kit_pass|||");
								p.CreatePacket(peer);
							}
							else if (cch.find("buttonClicked|claim-2592") != string::npos) {
									//int item = atoi(cch.substr(57, cch.length() - 57).c_str());
									if (pInfo(peer)->claim_kit4 == false) {
										int count = 1, itemID = 0;
										if (modify_inventory(peer, 2592, count) == 0) {//, 1782
											pInfo(peer)->claim_kit4 = true;
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											{
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("Congratulations! You have received " + to_string(count) + " `8" + items[2592].ori_name + "`` from KitPass Reward!");
												p.Insert(0), p.Insert(0);
												p.CreatePacket(peer);
											}
											PlayerMoving data_{};
											data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
											BYTE* raw = packPlayerMoving(&data_);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw;
											kit_Pass(peer, true, "tab_1", 0);
										}
										else {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("You have full inventory space!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
									}
								}
							//kit6
							else if (cch.find("buttonClicked|info_9908") != string::npos) {
								string pass = "";
								if (pInfo(peer)->Kit_Poin >= 4999 && pInfo(peer)->claim_kit5 == false) pass += "\nadd_button|claim-9908|`wClaim Rewards``|noflags|0|0|";
								else  pass += "\nadd_button||`wRewards Locked``|off|0|0|";
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|\nadd_label_with_icon|big|Claim `3" + items[9908].ori_name + "`` |left|9908|"
									"\nadd_spacer|small|"
									"\nadd_textbox|`wYou can claim `5" + items[9908].ori_name + "`` If Your KitPass lvl 6 & point `25000!``|left|"
									"\nadd_spacer|small|" + pass + "\nadd_spacer|small|\nadd_button|tab_1|`wBack to Menu``|noflags|0|0|\nend_dialog|kit_pass|||");
								p.CreatePacket(peer);
								}
							else if (cch.find("buttonClicked|claim-9908") != string::npos) {
									if (pInfo(peer)->claim_kit5 == false) {
										int count = 1, itemID = 0;
										if (modify_inventory(peer, 9908, count) == 0) {
											pInfo(peer)->claim_kit5 = true;
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											{
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("Congratulations! You have received " + to_string(count) + " `8" + items[9908].ori_name + "`` from KitPass Reward!");
												p.Insert(0), p.Insert(0);
												p.CreatePacket(peer);
											}
											PlayerMoving data_{};
											data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
											BYTE* raw = packPlayerMoving(&data_);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw;
											kit_Pass(peer, true, "tab_1", 0);
										}
										else {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("You have full inventory space!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
									}
								}
							break;
						}					
						else if (cch == "action|trade_cancel\n") cancel_trade(peer);
						if (pInfo(peer)->trading_with == -1) {
							if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|newbie\n\n") {
								{
									gamepacket_t p(7500), p2, p3;
									p.Insert("OnClearNPCMessage"), p.CreatePacket(peer);
									p2.Insert("OnAddNotification"), p2.Insert("interface/tutorial/tut07_create_world.rttex"), p2.Insert("`wLet's create a worlds! You can create a worlds by enter a random worlds and lock it!``"), p2.Insert("audio/tip_start.wav"), p2.Insert(1), p2.CreatePacket(peer);
									p3.Insert("OnPersistentNPCMessage"), p3.Insert(4032), p3.Insert("Welcome to Growtopia Private Server! Type /help to see all commands.\n`2Pickup`` your newbie rewards and start the journey!"), p3.Insert(1), p3.CreatePacket(peer);
								}
								pInfo(peer)->n = 1;
								if (pInfo(peer)->cc == 0) {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`oYou has been received `9Starter Pack`o, do /niuber before play this server. enjoy(love)");
									p.CreatePacket(peer);
									cout << "A new account has been created, name " + pInfo(peer)->tankIDName + " clicked starter pack" << endl;
									pInfo(peer)->cc = 1;
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|sessionlength_edit") != string::npos) {
								try {
									string name_ = pInfo(peer)->world;
									vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									if (p != worlds.end()) {
										World* world_ = &worlds[p - worlds.begin()];
										if (pInfo(peer)->tankIDName != world_->owner_name) break;
										world_->World_Time = (atoi(explode("\n", explode("checkbox_5|", cch)[1])[0].c_str()) == 1 ? 5 : (atoi(explode("\n", explode("checkbox_10|", cch)[1])[0].c_str()) == 1 ? 10 : (atoi(explode("\n", explode("checkbox_20|", cch)[1])[0].c_str()) == 1 ? 20 : (atoi(explode("\n", explode("checkbox_30|", cch)[1])[0].c_str()) == 1 ? 30 : (atoi(explode("\n", explode("checkbox_40|", cch)[1])[0].c_str()) == 1 ? 40 : (atoi(explode("\n", explode("checkbox_50|", cch)[1])[0].c_str()) == 1 ? 50 : (atoi(explode("\n", explode("checkbox_60|", cch)[1])[0].c_str()) == 1 ? 60 : 0)))))));
										gamepacket_t p;
										p.Insert("OnTalkBubble"); p.Insert(pInfo(peer)->netID);
										p.Insert((world_->World_Time == 0 ? "World Timer limit removed!" : "World Timer limit set to `2" + to_string(world_->World_Time) + " minutes``."));
										p.Insert(0); p.Insert(0); p.CreatePacket(peer);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == world_->name) {
												if (pInfo(currentPeer)->tankIDName != world_->owner_name && world_->World_Time != 0) {
													pInfo(currentPeer)->World_Timed = time(nullptr) + (world_->World_Time * 60);
													pInfo(currentPeer)->WorldTimed = true;
												}
											}
										}
									}
								}
								catch (out_of_range) {
									cout << "Server error invalid (out of range) on " + cch << endl;
									break;
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|worldcategory") != string::npos) {
								string Cat = "None";
								if (cch.find("buttonClicked|cat10") != string::npos) {
									Cat = "Storage";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|10\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat11") != string::npos) {
									Cat = "Story";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|11\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat12") != string::npos) {
									Cat = "Trade";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|12\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat14") != string::npos) {
									Cat = "Puzzle";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|14\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat15") != string::npos) {
									Cat = "Music";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|15\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat0") != string::npos) {
									Cat = "None";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|0\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat1") != string::npos) {
									Cat = "Adventure";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|1\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat2") != string::npos) {
									Cat = "Art";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|2\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat3") != string::npos) {
									Cat = "Farm";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|3\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat4") != string::npos) {
									Cat = "Game";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|4\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat5") != string::npos) {
									Cat = "Information";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|5\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat6") != string::npos) {
									Cat = "Parkour";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|6\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat7") != string::npos) {
									Cat = "Roleplay";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|7\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat8") != string::npos) {
									Cat = "Shop";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|8\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|cat9") != string::npos) {
									Cat = "Social";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSet World Category``|left|3802|\nembed_data|chosencat|9\nadd_textbox|Are you sure you want to change your world's category to " + Cat + "?|left|\nadd_smalltext|`4Warning:`` Changing your category will delete all ratings on your world .|left|\nend_dialog|worldcategory|Nevermind|Change Category|");
									p.CreatePacket(peer);
									break;
								}
								else {
									int Category = atoi(explode("\n", explode("chosencat|", cch)[1])[0].c_str());
									if (Category < 0 or Category > 15) break;
									string Cat = "None";
									if (Category == 0) Cat = "None"; if (Category == 1) Cat = "Adventure"; if (Category == 2) Cat = "Art"; if (Category == 3) Cat = "Farm"; if (Category == 4) Cat = "Game"; if (Category == 5) Cat = "Information"; if (Category == 15) Cat = "Music"; if (Category == 6) Cat = "Parkour"; if (Category == 14) Cat = "Puzzle"; if (Category == 7) Cat = "Roleplay"; if (Category == 8) Cat = "Shop"; if (Category == 9) Cat = "Social"; if (Category == 10) Cat = "Storage"; if (Category == 11) Cat = "Story"; if (Category == 12) Cat = "Trade";
									try {
										string name_ = pInfo(peer)->world;
										vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
										if (p != worlds.end()) {
											World* world_ = &worlds[p - worlds.begin()];
											if (pInfo(peer)->tankIDName != world_->owner_name) break;
											world_->World_Rating = 0;
											world_->Category = Cat;
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("This world has been moved to the '" + Cat + "' category! Everyone, please type `2/rate`` to rate it from 1-5 stars.");
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == world_->name) {
													p.CreatePacket(currentPeer);
												}
											}
										}
									}
									catch (out_of_range) {
										cout << "Server error invalid (out of range) on " + cch << endl;
										break;
									}
									break;
								}
								break;
							}
							if (cch.find("action|dialog_return\ndialog_name|bannerbandolier") != std::string::npos) {
								if (cch.find("buttonClicked|patternpicker") != std::string::npos) {
									string dialog = "";
									if (pInfo(peer)->Banner_Flag == 0) dialog += "set_default_color|`o\nadd_label_with_icon|big|`wBanner Bandolier``|left|5838|";
									else if (pInfo(peer)->Banner_Flag == 1) dialog += "set_default_color|`o\nadd_label_with_icon|big|`wBanner Bandolier``|left|5844|";
									else if (pInfo(peer)->Banner_Flag == 2) dialog += "set_default_color|`o\nadd_label_with_icon|big|`wBanner Bandolier``|left|5848|";
									else if (pInfo(peer)->Banner_Flag == 3) dialog += "set_default_color|`o\nadd_label_with_icon|big|`wBanner Bandolier``|left|5846|";
									else if (pInfo(peer)->Banner_Flag == 4) dialog += "set_default_color|`o\nadd_label_with_icon|big|`wBanner Bandolier``|left|5842|";
									dialog += "\nadd_spacer|small|\nadd_textbox|Pick a pattern for your banner.|left|\nadd_spacer|small|";
									dialog += "\nadd_label_with_icon_button|big|Harlequin|left|5838|pattern_1|\nadd_spacer|small|";
									dialog += "\nadd_label_with_icon_button|big|Slant|left|5844|pattern_2|\nadd_spacer|small|";
									dialog += "\nadd_label_with_icon_button|big|Stripe|left|5848|pattern_3|\nadd_spacer|small|";
									dialog += "\nadd_label_with_icon_button|big|Panel|left|5846|pattern_4|\nadd_spacer|small|";
									dialog += "\nadd_label_with_icon_button|big|Cross|left|5842|pattern_5|\nadd_spacer|small|";
									dialog += "\nend_dialog|bannerbandolier|Cancel||\nadd_quick_exit|";
									gamepacket_t p;
									p.Insert("OnDialogRequest"), p.Insert(dialog), p.CreatePacket(peer);
									break;
								}
								else if (cch.find("buttonClicked|pattern_") != std::string::npos) {
									int Pattern = atoi(cch.substr(49 + 22, cch.length() - 49 + 22).c_str());
									pInfo(peer)->CBanner_Item = pInfo(peer)->Banner_Item;
									pInfo(peer)->CBanner_Flag = Pattern - 1;
									SendBannerBandolier2(peer);
									break;
								}
								else if (cch.find("buttonClicked|reset") != std::string::npos) {
									pInfo(peer)->CBanner_Item = 0; pInfo(peer)->CBanner_Flag = 0; pInfo(peer)->Banner_Item = 0; pInfo(peer)->Banner_Flag = 0;
									SendBannerBandolier2(peer);
									break;
								}
								else if (!(cch.find("buttonClicked|patternpicker") != std::string::npos || cch.find("buttonClicked|pattern_") != std::string::npos || cch.find("\nbanneritem|") != std::string::npos)) {
									if (pInfo(peer)->CBanner_Item != 0) pInfo(peer)->Banner_Item = pInfo(peer)->CBanner_Item;
									if (pInfo(peer)->CBanner_Flag != 0) pInfo(peer)->Banner_Flag = pInfo(peer)->CBanner_Flag;
									pInfo(peer)->CBanner_Item = 0; pInfo(peer)->CBanner_Flag = 0;
									update_clothes(peer);
									break;
								}
								else {
									pInfo(peer)->CBanner_Flag = pInfo(peer)->CBanner_Flag;
									pInfo(peer)->CBanner_Item = atoi(explode("\n", explode("banneritem|", cch)[1])[0].c_str());
									SendBannerBandolier2(peer);
									break;
								}
								break;
							}
							if (cch.find("action|dialog_return\ndialog_name|punish_view\nbuttonClicked|warp_to_") != string::npos) {
								if (pInfo(peer)->mod == 1 || pInfo(peer)->dev == 1) {
									string world_name = cch.substr(67, cch.length() - 67);
									replace_str(world_name, "\n", "");
									replace_str(world_name, "reason|", "");
									join_world(peer, world_name);
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|top_richest\nbuttonClicked|userinfo_") != string::npos) {
							string username = cch.substr(68, cch.length() - 68);
							replace_str(username, "\n", "");
							bool foundacc = true;
							pInfo(peer)->last_wrenched = username;
							string bans = "", logs = "", mac = "", worlds_owned_ = "";
							//if (to_lower(pInfo(peer)->last_wrenched) == creator1) break;
							for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
								if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
									time_t s__;
									s__ = time(NULL);
									int days_ = int(s__) / (60 * 60 * 24);
									double hours_ = (double)((s__ - pInfo(currentPeer)->playtime) + pInfo(currentPeer)->seconds) / 3600;
									string num_text = to_string(hours_);
									string rounded = num_text.substr(0, num_text.find(".") + 3);
									foundacc = false;
									int adaBrpGems = 0, totalNetWorth = 0, totalWls = 0, totalBank = 0;
									totalWls = pInfo(currentPeer)->totalWls;
									totalNetWorth = pInfo(currentPeer)->totalNetWorth;
									totalBank = pInfo(currentPeer)->bankfixd;
									int dls = 0, wls = 0, bgl = 0;
									dls = pInfo(currentPeer)->totalWls / 100;
									wls = pInfo(currentPeer)->totalWls - (dls * 100);
									if (dls >= 100) {
										bgl = pInfo(currentPeer)->totalWls / 10000;
										dls -= 100 * bgl;
									}
									string clothes = "", WorldLock = "";
									if (wls != 0) WorldLock += "\nadd_smalltext|Locks in backpack:|\nadd_label_with_icon|small|" + to_string(wls) + " " + items[242].ori_name + "|left|242|";
									if (dls != 0) WorldLock += "\nadd_label_with_icon|small|" + to_string(dls) + " " + items[1796].ori_name + "|left|1796|";
									if (bgl != 0) WorldLock += "\nadd_label_with_icon|small|" + to_string(bgl) + " " + items[7188].ori_name + "|left|7188|";
									// int hair = 0, shirt = 0, pants = 0, feet = 0, face = 0, hand = 0, back = 0, mask = 0, necklace = 0, ances = 0;
									if (pInfo(currentPeer)->mask != 0) clothes += "\nadd_label_with_icon|small|" + items[pInfo(currentPeer)->mask].ori_name + "|left|" + to_string(pInfo(currentPeer)->mask) + "|";
									if (pInfo(currentPeer)->face != 0) clothes += "\nadd_label_with_icon|small|" + items[pInfo(currentPeer)->face].ori_name + "|left|" + to_string(pInfo(currentPeer)->face) + "|";
									if (pInfo(currentPeer)->hair != 0) clothes += "\nadd_label_with_icon|small|" + items[pInfo(currentPeer)->hair].ori_name + "|left|" + to_string(pInfo(currentPeer)->hair) + "|";
									if (pInfo(currentPeer)->necklace != 0) clothes += "\nadd_label_with_icon|small|" + items[pInfo(currentPeer)->necklace].ori_name + "|left|" + to_string(pInfo(currentPeer)->necklace) + "|";
									if (pInfo(currentPeer)->shirt != 0) clothes += "\nadd_label_with_icon|small|" + items[pInfo(currentPeer)->shirt].ori_name + "|left|" + to_string(pInfo(currentPeer)->shirt) + "|";
									if (pInfo(currentPeer)->back != 0) clothes += "\nadd_label_with_icon|small|" + items[pInfo(currentPeer)->back].ori_name + "|left|" + to_string(pInfo(currentPeer)->back) + "|";
									if (pInfo(currentPeer)->pants != 0) clothes += "\nadd_label_with_icon|small|" + items[pInfo(currentPeer)->pants].ori_name + "|left|" + to_string(pInfo(currentPeer)->pants) + "|";
									if (pInfo(currentPeer)->feet != 0) clothes += "\nadd_label_with_icon|small|" + items[pInfo(currentPeer)->feet].ori_name + "|left|" + to_string(pInfo(currentPeer)->feet) + "|";
									if (pInfo(currentPeer)->hand != 0) clothes += "\nadd_label_with_icon|small|" + items[pInfo(currentPeer)->hand].ori_name + "|left|" + to_string(pInfo(currentPeer)->hand) + "|";
									if (pInfo(currentPeer)->ances != 0) clothes += "\nadd_label_with_icon|small|" + items[pInfo(currentPeer)->ances].ori_name + "|left|" + to_string(pInfo(currentPeer)->ances) + "|";

									string lbdialog = "`o\n\nadd_player_info|`0" + pInfo(currentPeer)->modName + "``|" + (pInfo(currentPeer)->level >= 125 ? "125|5001000|5001000|" : "") + "" + (pInfo(currentPeer)->level <= 125 ? to_string(pInfo(currentPeer)->level) + "|" + to_string(pInfo(currentPeer)->xp) + "|" + to_string(50 * ((pInfo(currentPeer)->level * pInfo(currentPeer)->level) + 2)) : "") + "\nadd_spacer|small|\nadd_textbox|Account Net. Worth: `w" + fixint(totalNetWorth) + " `9World Locks|\nadd_textbox|Account Playtime: `5" + rounded + " ``Hours|\nadd_spacer|small|\nadd_spacer|small|\nadd_label_with_icon|small|Total Bgl in the bank: " + fixint(totalBank) + "|left|7188|\nadd_label_with_icon|small|Total Gems: " + fixint(pInfo(currentPeer)->gems) + "|left|9438|\nadd_spacer|small|\nadd_spacer|small|\nadd_label_with_icon|small|Total World Locks: " + fixint(totalWls) + "|left|242|" + WorldLock + "\nadd_spacer|small|\nadd_label_with_icon|small|Total Worlds Owned: " + fixint(pInfo(currentPeer)->worlds_owned.size()) + "|left|3802|\nadd_smalltext|Total Inventory Space: " + fixint(pInfo(currentPeer)->inv.size()) + "|\nadd_spacer|small|\nadd_smalltext|Clothing (Set):|" + clothes + "\nadd_spacer|small|\nadd_spacer|small|\nadd_smalltext|`5(User information refresh every minute in real-time)``|\nadd_button|backtolb|Back|noflags|0|0|\nend_dialog|userinfo|Exit||\nadd_quick_exit|\n";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|" + lbdialog);
									p.CreatePacket(peer);
								}
							}
							if (foundacc) {
								try {
									int playerLevel = 0, playerXp = 0, adaBrpGems = 0, gemsToWl = 0, totalNetWorth = 0, totalWls = 0, totalBank = 0, aspectOwned = 0, aspectPurchased = 0, clothHair = 0, clothMask = 0, clothFace = 0, clothNeck = 0, clothBack = 0, clothShirt = 0, clothPants = 0, clothFeet = 0, clothAnces = 0, clothHand = 0;
									string clothes = "", modName = "";
									ifstream ifs("database/players/" + username + "_.json");
									if (ifs.is_open()) {
										json j;
										ifs >> j;
										// get data
										modName = (!(j.find("modname") != j.end()) ? username : j["modname"].get<string>());
										playerLevel = j["level"].get<int>();
										playerXp = j["xp"].get<int>();
										clothHair = j["hair"].get<int>();
										clothMask = j["mask"].get<int>();
										clothFace = j["face"].get<int>();
										clothNeck = j["necklace"].get<int>();
										clothBack = j["back"].get<int>();
										clothShirt = j["shirt"].get<int>();
										clothPants = j["pants"].get<int>();
										clothFeet = j["feet"].get<int>();
										clothAnces = j["ances"].get<int>();
										clothHand = j["hand"].get<int>();
										aspectOwned = j["gtwl"].get<int>();
										aspectPurchased = (!(j.find("Total_TopUp") != j.end()) ? 0 : j["Total_TopUp"].get<int>());
										adaBrpGems = j["gems"].get<int>();
										totalWls = (!(j.find("Total_Wls") != j.end()) ? 0 : j["Total_Wls"].get<int>());
										totalBank = j["bank_c"].get<uint8_t>();
									}
									if (clothMask != 0) clothes += "\nadd_label_with_icon|small|" + items[clothMask].ori_name + "|left|" + to_string(clothMask) + "|";
									if (clothHair != 0) clothes += "\nadd_label_with_icon|small|" + items[clothHair].ori_name + "|left|" + to_string(clothHair) + "|";
									if (clothFace != 0) clothes += "\nadd_label_with_icon|small|" + items[clothFace].ori_name + "|left|" + to_string(clothFace) + "|";
									if (clothNeck != 0) clothes += "\nadd_label_with_icon|small|" + items[clothNeck].ori_name + "|left|" + to_string(clothNeck) + "|";
									if (clothBack != 0) clothes += "\nadd_label_with_icon|small|" + items[clothBack].ori_name + "|left|" + to_string(clothBack) + "|";
									if (clothShirt != 0) clothes += "\nadd_label_with_icon|small|" + items[clothShirt].ori_name + "|left|" + to_string(clothShirt) + "|";
									if (clothPants != 0) clothes += "\nadd_label_with_icon|small|" + items[clothPants].ori_name + "|left|" + to_string(clothPants) + "|";
									if (clothFeet != 0) clothes += "\nadd_label_with_icon|small|" + items[clothFeet].ori_name + "|left|" + to_string(clothFeet) + "|";
									if (clothAnces != 0) clothes += "\nadd_label_with_icon|small|" + items[clothAnces].ori_name + "|left|" + to_string(clothAnces) + "|";
									if (clothHand != 0) clothes += "\nadd_label_with_icon|small|" + items[clothHand].ori_name + "|left|" + to_string(clothHand) + "|";
									if (adaBrpGems >= 2000) adaBrpGems = gemsToWl / 2000;
									totalNetWorth = adaBrpGems + totalWls;
									string lbdialog = "`o\n\nadd_player_info|`0" + modName + "``|" + (playerLevel >= 125 ? "125|5001000|5001000|" : "") + "" + (playerLevel <= 125 ? to_string(playerLevel) + "|" + to_string(playerXp) + "|" + to_string(50 * ((playerLevel * playerXp) + 2)) : "") + "\nadd_spacer|small|\nadd_textbox|Account Net. Worth: `w" + fixint(totalNetWorth) + " `9World Locks|\nadd_textbox|The user is currently `4OFFLINE``|\nadd_spacer|small|\nadd_spacer|small|\nadd_label_with_icon|small|Total Bgl in the bank: " + fixint(totalBank) + "|left|7188|\nadd_label_with_icon|small|Total Gems: " + fixint(adaBrpGems) + "|left|9438|\nadd_label_with_icon|small|Total World Locks: " + fixint(totalWls) + "|left|242|\nadd_spacer|small|\nadd_smalltext|Clothing (Set):|" + clothes + "\nadd_spacer|small|\nadd_spacer|small|\nadd_smalltext|`5(User information refresh every minute in real-time)``|\nadd_button|backtolb|Back|noflags|0|0|\nend_dialog|userinfo|Exit||\nadd_quick_exit|\n";
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|" + lbdialog);
									p.CreatePacket(peer);
								}//back here
								catch (exception& e) {
									xItsCrims_warn(e.what());
									break;
								}
							}
							break;
						}
						else if (cch == "action|dialog_return\ndialog_name|userinfo\nbuttonClicked|backtolb\n\n") {
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`wTop Richest Leaderboard``|left|10864|\nadd_spacer|" + top_rich_list + "\nadd_button|\nend_dialog|top_richest|Close||\n");
								p.CreatePacket(peer);
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|top_richest\nbuttonClicked|socialportal\n\n") {
								send_social(peer);
								break;
						}
							else if (cch.find("action|dialog_return\ndialog_name|blast\nitemID|") != string::npos) {
							string world = cch.substr(57, cch.length() - 57).c_str();
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								int blast = atoi(explode("\n", t_[3])[0].c_str()), got = 0;
								modify_inventory(peer, blast, got);
								if (got == 0) break;
								replace_str(world, "\n", "");
								transform(world.begin(), world.end(), world.begin(), ::toupper);
								if (find_if(worlds.begin(), worlds.end(), [world](const World& a) { return a.name == world; }) != worlds.end() || not check_blast(world) || _access_s(("database/worlds/" + world + "_.json").c_str(), 0) == 0) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("That world name already exists. You'll have to be more original. Maybe add some numbers after it?"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
								}
								else {
									if (modify_inventory(peer, blast, got = -1) == 0) {
										create_world_blast(world, blast);
										if (blast == 830) modify_inventory(peer, 834, got = -100);
										join_world(peer, world);
										gamepacket_t p(750), p2(750);
										p.Insert("OnConsoleMessage"), p.Insert("** `5"+pInfo(peer)->tankIDName + " activates a " + items[blast].name + "! ``**"), p.CreatePacket(peer);
										p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("** `5" + pInfo(peer)->tankIDName + " activates a " + items[blast].name + "! ``**"), p2.Insert(0), p2.Insert(1), p2.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|consumehgem\nitemID|6200|\ncount|") != string::npos) {
								string itemCount = cch.substr(64, cch.length() - 64).c_str();
								int intItemCount = atoi(itemCount.c_str());
								if (intItemCount <= 0) break;
								int got = 0;
								int remove = -intItemCount;
								modify_inventory(peer, 4490, got);
								if (got == 0) break;
								if (modify_inventory(peer, 4490, remove) == 0) {
									int total = intItemCount * 1000;
									pInfo(peer)->gems += total;
									{
										gamepacket_t p;
										p.Insert("OnSetBux");
										p.Insert(pInfo(peer)->gems);
										p.Insert(0);
										p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
										if (pInfo(peer)->supp >= 2) {
											p.Insert((float)33796, (float)1, (float)0);
										}
										p.CreatePacket(peer);
									}
								}
								break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|megaphone\nitemID|2480|\nwords|") != string::npos) {
								string text = cch.substr(62, cch.length() - 62).c_str();
								bool cansb = true;
								int c_ = 0;
								modify_inventory(peer, 2480, c_);
								if (c_ == 0) continue;
								if (has_playmod(pInfo(peer), "duct tape")) {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`6>> That's sort of hard to do while duct-taped.``");
									p.CreatePacket(peer);
									cansb = false;
									continue;
								}
								if (has_playmod(pInfo(peer), "megaphone!")) {
									int time_ = 0;
									for (PlayMods peer_playmod : pInfo(peer)->playmods) {
										if (peer_playmod.id == 13) {
											time_ = peer_playmod.time - time(nullptr);
											break;
										}
									}
									packet_(peer, "action|log\nmsg|>> (" + to_playmod_time(time_) + "before you can broadcast again)", "");
									break;
								}
								if (cansb) {
									replace_str(text, "\n", "");
									pInfo(peer)->usedmegaphone = 1;
									SendCmd(peer, "/sb " + text, false);
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|notebook_edit\nbuttonClicked|cancel") != string::npos || cch.find("action|dialog_return\ndialog_name|notebook_edit\nbuttonClicked|clear") != string::npos) {
								if (cch.find("action|dialog_return\ndialog_name|notebook_edit\nbuttonClicked|clear") != string::npos) 	pInfo(peer)->note = "";
								send_wrench_self(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|notebook_edit\nbuttonClicked|save\n\npersonal_note|") != string::npos) {
								string btn = cch.substr(81, cch.length() - 81).c_str();
								replace_str(btn, "\n", "");
								if (btn.length() > 128) continue;
								pInfo(peer)->note = btn;
								send_wrench_self(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|3898\nbuttonClicked|") != string::npos|| cch == "action|dialog_return\ndialog_name|zurgery_back\nbuttonClicked|53785\n\n" || cch == "action|dialog_return\ndialog_name|zombie_back\nbuttonClicked|53785\n\n") {
								string btn = cch.substr(52, cch.length() - 52).c_str();
								if (cch == "action|dialog_return\ndialog_name|zurgery_back\nbuttonClicked|53785\n\n" || cch == "action|dialog_return\ndialog_name|zombie_back\nbuttonClicked|53785\n\n") btn = "53785";
								replace_str(btn, "\n", "");
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								if (btn == "12345") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wCrazy Jim's Quest Emporium``|left|3902|\nadd_textbox|HEEEEYYY there Growtopian! I'm Crazy Jim, and my quests are so crazy they're KERRRRAAAAZZY!! And that is clearly very crazy, so please, be cautious around them. What can I do ya for, partner?|left|\nadd_button|chc1_1|Daily Quest|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
								else if (btn == "53785") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSales-Man``|left|4358|\nadd_textbox|It is I, Sales-Man, savior of the wealthy! Let me rescue you from your riches. What would you like to buy today?|left|\nadd_button|chc4_1|Surgery Items|noflags|0|0|\nadd_button|chc3_1|Zombie Defense Items|noflags|0|0|\nadd_button|chc2_1|Blue Gem Lock|noflags|0|0|\nadd_button|chc0_1|Diamond Lock|noflags|0|0|\nadd_button|convert_bgl|GEMS TO BGL|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
								else if (btn == "chc1_1") {
									if (today_day != pInfo(peer)->dd) {
										int haveitem1 = 0, haveitem2 = 0, received = 0;
										modify_inventory(peer, item1, haveitem1);
										modify_inventory(peer, item2, haveitem2);
										if (haveitem1 >= item1c && haveitem2 >= item2c) received = 1;
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wCrazy Jim's Daily Quest``|left|3902|\nadd_textbox|I guess some people call me Crazy Jim because I'm a bit of a hoarder. But I'm very particular about what I want! And today, what I want is this:|left|\nadd_label_with_icon|small|`2" + to_string(item1c) + " " + items[item1].name + "|left|" + to_string(item1) + "|\nadd_smalltext|and|left|\nadd_label_with_icon|small|`2" + to_string(item2c) + " " + items[item2].name + "|left|" + to_string(item2) + "|\nadd_spacer|small|\nadd_smalltext|You shove all that through the phone (it works, I've tried it), and I will hand you one of the `2Growtokens`` from my personal collection!  But hurry, this offer is only good until midnight, and only one `2Growtoken`` per person!|left|\nadd_spacer|small|\nadd_smalltext|`6(You have " + to_string(haveitem1) + " " + items[item1].name + " and " + to_string(haveitem2) + " " + items[item2].name + ")``|left|\nadd_spacer|small|" + (received == 1 ? "\nadd_button|turnin|Turn in items|noflags|0|0|" : "") + "\nadd_spacer|small|\nadd_button|12345|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
									}
									else p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wCrazy Jim's Daily Quest``|left|3902|\nadd_textbox|You've already completed my Daily Quest for today! Call me back after midnight to hear about my next cravings.|left|\nadd_button|12345|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
								}
								else if (btn == "turnin") {
									if (today_day != pInfo(peer)->dd) {
										int haveitem1 = 0, haveitem2 = 0, received = 0, remove = -1, remove2 = -1, giveitem = 1;
										modify_inventory(peer, item1, haveitem1);
										modify_inventory(peer, item2, haveitem2);
										if (haveitem1 >= item1c && haveitem2 >= item2c) received = 1;
										if (pInfo(peer)->quest_active && pInfo(peer)->quest_step == 6 && pInfo(peer)->quest_progress < 28) {
											pInfo(peer)->quest_progress += received;
											if (pInfo(peer)->quest_progress >= 28) {
												pInfo(peer)->quest_progress = 28;
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("`9Legendary Quest step complete! I'm off to see a Wizard!");
												p.Insert(0), p.Insert(0);
												p.CreatePacket(peer);
											}
										}
										if (received == 1) {
											pInfo(peer)->dd = today_day;
											modify_inventory(peer, item1, remove *= item1c);
											modify_inventory(peer, item2, remove2 *= item2c);
											modify_inventory(peer, 1486, giveitem);
											{
												{
													string name_ = pInfo(peer)->world;
													vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
													if (p != worlds.end()) {
														World* world_ = &worlds[p - worlds.begin()];
														PlayerMoving data_{};
														data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16;
														data_.packetType = 19, data_.plantingTree = 500;
														data_.punchX = 1486, data_.punchY = pInfo(peer)->netID;
														int32_t to_netid = pInfo(peer)->netID;
														BYTE* raw = packPlayerMoving(&data_);
														raw[3] = 5;
														memcpy(raw + 8, &to_netid, 4);
														for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
															if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
															if (pInfo(currentPeer)->world == world_->name) {
																send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
															}
														}
														delete[] raw;
													}
												}
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("[`6You jammed " + to_string(item1c) + " " + items[item1].name + " and " + to_string(item2c) + " " + items[item2].name + " into the phone, and 1 `2Growtoken`` popped out!``]");
												p.CreatePacket(peer);
											}
										}
									}
									else {
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wCrazy Jim's Daily Quest``|left|3902|\nadd_textbox|You've already completed my Daily Quest for today! Call me back after midnight to hear about my next cravings.|left|\nadd_button|12345|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
										p.CreatePacket(peer);
									}
								}
								else if (btn == "chc2_1") {
									int c_ = 0;
									modify_inventory(peer, 1796, c_);
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wBlue Gem Lock``|left|7188|\nadd_textbox|Excellent! I'm happy to sell you a Blue Gem Lock in exchange for 100 Diamond Lock..|left|\nadd_smalltext|`6You have " + to_string(c_) + " Diamond Lock.``|left|" + (c_ >= 100 ? "\nadd_button|chc2_2_1|Thank you!|noflags|0|0|" : "") + "\nadd_button|53785|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
								}
								//2500000000
						    	else if (btn == "chc0_1") {
								int c_ = pInfo(peer)->gems;
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wDiamond Lock``|left|1796|\nadd_textbox|Excellent! I'm happy to sell you a Diamond Lock in exchange for 200.000 Gems.|left|\nadd_smalltext|`6You have " + fixint(c_) + " Gems.``|left|" + (c_ >= 200000 ? "\nadd_button|chc0_2_1|Thank you!|noflags|0|0|" : "") + "\nadd_button|53785|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
							}
								else if (btn == "convert_bgl") {
								int current_gems = pInfo(peer)->gems;
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wBlue Gem Lock|left|7188|\nadd_textbox|`$Excellent! I'm happy to sell you Blue Gem Lock in exchange for 25,000,000|\nadd_smalltext|`6You have " + to_string(current_gems) + "|" + (current_gems >= 25000000 ? "\nadd_button|convert_start|`oConvert Blue Gem Lock|noflags|0|0|" : "") + "\nadd_button|53785|Back|noflags|0|0|\nend_dialog|3898|Hang Up||");
							}
								else if (btn == "chc0_2_1") {
								int c_ = pInfo(peer)->gems, c1796 = 0, additem = 0;
								modify_inventory(peer, 1796, c1796);
								if (c_ < 200000) continue;
								if (c1796 >= 200) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("You don't have room in your backpack!");
									p.Insert(0), p.Insert(1);
									p.CreatePacket(peer);
									{
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("You don't have room in your backpack!");
										p.CreatePacket(peer);
									}
									continue;
								}
								if (c_ >= 200000) {
									if (get_free_slots(pInfo(peer)) >= 2) {
										int cz_ = 200000;
										if (modify_inventory(peer, 1796, additem = 1) == 0) {
											{
												{
													pInfo(peer)->gems -= cz_;
													string name_ = pInfo(peer)->world;
													vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
													if (p != worlds.end()) {
														gamepacket_t p8;
														p8.Insert("OnSetBux");
														p8.Insert(pInfo(peer)->gems);
														p8.Insert(0);
														p8.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
														if (pInfo(peer)->supp >= 2) {
															p8.Insert((float)33796, (float)1, (float)0);
														}
														p8.CreatePacket(peer);
														World* world_ = &worlds[p - worlds.begin()];
														PlayerMoving data_{};
														data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16;
														data_.packetType = 19, data_.plantingTree = 500;
														data_.punchX = 1796, data_.punchY = pInfo(peer)->netID;
														int32_t to_netid = pInfo(peer)->netID;
														BYTE* raw = packPlayerMoving(&data_);
														raw[3] = 5;
														memcpy(raw + 8, &to_netid, 4);
														for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
															if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
															if (pInfo(currentPeer)->world == world_->name) {
																send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
															}
														}
														delete[] raw;
													}
												}
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("[`6You spent 200.000 Gems to get 1 Diamond Lock``]");
												p.CreatePacket(peer);
											}
										}
										int c_ = pInfo(peer)->gems;
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wDiamond Lock``|left|1796|\nadd_textbox|Excellent! I'm happy to sell you a Diamond Lock in exchange for 200.000 Gems.|left|\nadd_smalltext|`6You have " + fixint(c_) + " Gems.``|left|" + (c_ >= 200000 ? "\nadd_button|chc0_2_1|Thank you!|noflags|0|0|" : "") + "\nadd_button|53785|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("You don't have enough inventory space!");
										p.CreatePacket(peer);
									}
								}
							}
								else if (btn == "chc2_1") {
								int c_ = 0;
								modify_inventory(peer, 1796, c_);
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wBlue Gem Lock``|left|7188|\nadd_textbox|Excellent! I'm happy to sell you a Blue Gem Lock in exchange for 100 Diamond Lock..|left|\nadd_smalltext|`6You have " + to_string(c_) + " Diamond Lock.``|left|" + (c_ >= 100 ? "\nadd_button|chc2_2_1|Thank you!|noflags|0|0|" : "") + "\nadd_button|53785|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
							}
								else if (btn == "convert_start") {
								int current_gems = pInfo(peer)->gems;
								int bgl = 0;
								modify_inventory(peer, 7188, bgl);
								if (bgl >= 200) {
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wBlue Gem Lock|left|7188|\nadd_smalltext|`4You are full of Blue Gem Lock|\nadd_textbox|`$Excellent! I'm happy to sell you Blue Gem Lock in exchange for 25,000,000|\nadd_smalltext|`6You have " + to_string(current_gems) + "|" + (current_gems >= 25000000 ? "\nadd_button|convert_start|`oConvert Blue Gem Lock|noflags|0|0|" : "") + "\nadd_button|53785|Back|noflags|0|0|\nend_dialog|3898|Hang Up||");
								}
								else {
									int get = 1;
									modify_inventory(peer, 7188, get);
									pInfo(peer)->gems -= 25000000;
									gamepacket_t bux;
									bux.Insert("OnSetBux");
									bux.Insert(pInfo(peer)->gems);
									bux.CreatePacket(peer);
									p.Insert("set_default_color|`o\nadd_textbox|`oSuccessfully convert Blue Gem Lock!|\nadd_spacer|small|\nadd_button|53785|Back|noflags|0|0|\nend_dialog|3898|||");
								}
								}

								else if (btn == "chc2_2_1") {
									int c7188 = 0, c1796 = 0, additem = 0;
									modify_inventory(peer, 1796, c1796);
									if (c1796 < 100) continue;
									modify_inventory(peer, 7188, c7188);
									if (c7188 >= 200) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You don't have room in your backpack!");
										p.Insert(0), p.Insert(1);
										p.CreatePacket(peer);
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("You don't have room in your backpack!");
											p.CreatePacket(peer);
										}
										continue;
									}
									if (c1796 >= 100) {
										if (get_free_slots(pInfo(peer)) >= 2) {
											int cz_ = 1;
											if (modify_inventory(peer, 1796, additem = -100) == 0) {
												modify_inventory(peer, 7188, additem = 1);
												{
													{
														string name_ = pInfo(peer)->world;
														vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
														if (p != worlds.end()) {
															World* world_ = &worlds[p - worlds.begin()];
															PlayerMoving data_{};
															data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16;
															data_.packetType = 19, data_.plantingTree = 500;
															data_.punchX = 7188, data_.punchY = pInfo(peer)->netID;
															int32_t to_netid = pInfo(peer)->netID;
															BYTE* raw = packPlayerMoving(&data_);
															raw[3] = 5;
															memcpy(raw + 8, &to_netid, 4);
															for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																if (pInfo(currentPeer)->world == world_->name) {
																	send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																}
															}
															delete[] raw;
														}
													}
													gamepacket_t p;
													p.Insert("OnConsoleMessage");
													p.Insert("[`6You spent 100 Diamond Lock to get 1 Blue Gem Lock``]");
													p.CreatePacket(peer);
												}
											}
											int c_ = 0;
											modify_inventory(peer, 1796, c_);
											p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wBlue Gem Lock``|left|7188|\nadd_textbox|Excellent! I'm happy to sell you a Blue Gem Lock in exchange for 100 Diamond Lock..|left|\nadd_smalltext|`6You have " + to_string(c_) + " Diamond Lock.``|left|" + (c_ >= 100 ? "\nadd_button|chc2_2_1|Thank you!|noflags|0|0|" : "") + "\nadd_button|53785|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("You don't have enough inventory space!");
										p.CreatePacket(peer);
									}
								}
								else if (btn == "chc3_1") {
								int zombie_brain = 0, pile = 0, total = 0;
								modify_inventory(peer, 4450, zombie_brain);
								modify_inventory(peer, 4452, pile);
								total += zombie_brain + (pile * 100);
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSales-Man: Zombie Defense``|left|4358|\nadd_textbox|Excellent! I'm happy to sell you Zombie Defense supplies in exchange for Zombie Brains.|left|\nadd_smalltext|You currently have " + setGems(total) + " Zombie Brains.|left|\nadd_spacer|small|\ntext_scaling_string|5,000ZB|\n" + zombie_list + "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_button|53785|Back|noflags|0|0|\nend_dialog|zombie_back|Hang Up||\n");
								p.CreatePacket(peer);
								}
								else if (btn == "chc4_1") {
								int zombie_brain = 0, pile = 0, total = 0;
								modify_inventory(peer, 4450, zombie_brain);
								modify_inventory(peer, 4300, pile);
								total += zombie_brain + (pile * 100);
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSales-Man: Surgery``|left|4358|\nadd_textbox|Excellent! I'm happy to sell you rare and precious Surgery prizes in exchange for Caduceus medals.|left|\nadd_smalltext|You currently have " + setGems(total) + " Caducei.|left|\nadd_spacer|small|\ntext_scaling_string|5,000ZB|\n" + surgery_list + "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_button|53785|Back|noflags|0|0|\nend_dialog|zurgery_back|Hang Up||\n");
								p.CreatePacket(peer);
								}
								else p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wDisconnected``|left|774|\nadd_textbox|The number you have tried to reach is disconnected. Please check yourself before you wreck yourself.|left|\nend_dialog|3898|Hang Up||\n");
								if (btn != "turnin") p.CreatePacket(peer);
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|pworld_view\nbuttonClicked|banworld\n\n") {
								string name_ = pInfo(peer)->wwop;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];

									if (not world_->nuked) {
										struct tm newtime;
										time_t now = time(0);
										localtime_s(&newtime, &now);
										world_->nuked = true;
										world_->n_t = "" + to_string(newtime.tm_mon + 1) + "/" + to_string(newtime.tm_mday) + "/2022 " + to_string(newtime.tm_hour) + ":" + (newtime.tm_min < 10 ? "0" + to_string(newtime.tm_min) + "" : "" + to_string(newtime.tm_min)) + ":" + to_string(newtime.tm_sec) + "";
										world_->n_b = pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``";
										gamepacket_t p;
										p.Insert("OnConsoleMessage"), p.Insert("`o>> `4" + world_->name + " `4was nuked from orbit`o. It's the only way to be sure. Play nice, everybody!");
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == pInfo(peer)->wwop and not pInfo(currentPeer)->mod and not pInfo(currentPeer)->dev) exit_(currentPeer);
											packet_(currentPeer, "action|play_sfx\nfile|audio/bigboom.wav\ndelayMS|0");
											p.CreatePacket(currentPeer);
										}
										add_modlogs(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, "NUKED WORLD: `#" + pInfo(peer)->wwop, "");
									}
									else {
										world_->nuked = false, world_->n_t = "", world_->n_b = "";
										gamepacket_t p;
										p.Insert("OnConsoleMessage"), p.Insert("This world is once again available to everyone!"), p.CreatePacket(peer);
										add_modlogs(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, "UNNUKED WORLD: `#" + pInfo(peer)->wwop, "");
									}
								}
						}
							else if (cch == "action|dialog_return\ndialog_name|pworld_view\nbuttonClicked|dcworld\n\n") {
								//	string world_name = cch.substr(67, cch.length() - 67);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->dev) continue;
									if (pInfo(currentPeer)->world == pInfo(peer)->wwop) {
										enet_peer_disconnect_later(currentPeer, 1);
									}
								}
							}
							else if (cch.find("action|itemfavourite") != string::npos) {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								uint16_t itemId = atoi(explode("\n", t_[3])[0].c_str());
								if (itemId >= 0 && itemId < items.size()) {
									if (items[itemId].blockType == BlockTypes::CLOTHING) {
										vector<int>& favList = pInfo(peer)->fav_list;
										auto it = find(favList.begin(), favList.end(), itemId);
										if (it == favList.end()) {
											favList.push_back(itemId);
											gamepacket_t p;
											p.Insert("OnFavItemUpdated"), p.Insert(itemId), p.Insert(1), p.CreatePacket(peer);
										}
										else {
											favList.erase(it);
											gamepacket_t p;
											p.Insert("OnFavItemUpdated"), p.Insert(itemId), p.Insert(0), p.CreatePacket(peer);
										}
									}
								}
								break;
}
							else if (cch == "action|inventoryfavuitrigger\n") {
								std::string fav_dialog = "set_default_color|`o\nadd_label_with_icon|big|`wFavorited Items``|left|13814|\nadd_spacer|small|\nadd_textbox|You have not favorited any item yet.|left|\nadd_spacer|small|\nend_dialog|unfavorite_items_dialog|Close||";
								std::string have_fav = "set_default_color|`o\nadd_label_with_icon|big|`wFavorited Items``|left|13814|\nadd_spacer|small|\nadd_textbox|All favorited items are currently in your inventory. They can be unfavorited by tapping on the UNFAV button while having the item selected in your inventory.|left|\nadd_spacer|small|\nend_dialog|unfavorite_items_dialog|Close||";
								vz::OnDialogRequest(peer, (pInfo(peer)->fav_list.empty()) ? fav_dialog : have_fav);
								break;
}

						else if (cch.find("action|dialog_return\ndialog_name|punish_view\nbuttonClicked|view_inventory") != string::npos) {
								if (pInfo(peer)->tankIDName == creator1) {
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
											string recently_visited = "";
											for (auto it = pInfo(currentPeer)->last_visited_worlds.rbegin(); it != pInfo(currentPeer)->last_visited_worlds.rend(); ++it) {
												string a_ = *it + (next(it) != pInfo(currentPeer)->last_visited_worlds.rend() ? "``, " : "``");
												recently_visited += "`#" + a_;
											}
											string inventory = "";
											int thats5 = 0, thatsadded = 0;
											for (int i_ = 0; i_ < pInfo(currentPeer)->inv.size(); i_++) {
												if (pInfo(currentPeer)->inv[i_].id == 0 || pInfo(currentPeer)->inv[i_].id == 18 || pInfo(currentPeer)->inv[i_].id == 32) continue;
												thats5++;
												thatsadded = 0;
												inventory += "\nadd_button_with_icon|" + (pInfo(peer)->dev == 1 ? to_string(pInfo(currentPeer)->inv[i_].id) : "") + "||staticBlueFrame|" + to_string(pInfo(currentPeer)->inv[i_].id) + "|" + to_string(pInfo(currentPeer)->inv[i_].count) + "|";
												if (thats5 >= 6) {
													thats5 = 0;
													thatsadded = 1;
													inventory += "\nadd_button_with_icon||END_LIST|noflags|0||";
												}
											}
											gamepacket_t p;
											p.Insert("OnDialogRequest");
											p.Insert("set_default_color|`o\nadd_label_with_icon|small|`0Inventory of " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``'s (" + pInfo(currentPeer)->requestedName + ") - #" + to_string(pInfo(currentPeer)->netID) + "|left|3802|\nadd_spacer|small|\nadd_textbox|Last visited: " + recently_visited + "|\nadd_textbox|Gems: `w" + setGems(pInfo(currentPeer)->gems) + "|\nadd_textbox|Backpack slots: `w" + to_string(pInfo(currentPeer)->inv.size() - 1) + "|" + inventory + "" + (thatsadded == 1 ? "" : "\nadd_button_with_icon||END_LIST|noflags|0||") + "|\nend_dialog|view_inventory|Continue||\nadd_quick_exit|");
											p.CreatePacket(peer);
										}
									}
								}
								break;
							}
							if (cch.find("action|dialog_return\ndialog_name|punish_view\nbuttonClicked|warp_to_") != string::npos) {
								if (pInfo(peer)->mod == 1 || pInfo(peer)->dev == 1) {
									string world_name = cch.substr(67, cch.length() - 67);
									vector<string> test = split_string_by_newline(world_name);
									join_world(peer, test[0]);
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|top\nbuttonClicked|warp_to_") != string::npos) {
								string world_name = cch.substr(59, cch.length() - 59);
								replace_str(world_name, "\n", "");
								join_world(peer, world_name);
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|top\nbuttonClicked|wotwlistback\n\n") {
								SendCmd(peer, "/top", true);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|shopgemsconfirm\ngemspurchase|") != string::npos) {
								int gems = atoi(cch.substr(62, cch.length() - 62).c_str());
								if (gems <= 0) break;
								pInfo(peer)->offergems = gems;
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Gems``|left|112|\n\nadd_spacer|small|\nadd_textbox|`2Purchase`` `9" + setGems(pInfo(peer)->offergems * 2000) + " Gems`` for `9" + to_string(gems) + " World Locks?``|\nadd_button|shopmoneybuy|`0Purchase``|NOFLAGS|0|0|\nadd_button||`0Cancel``|NOFLAGS|0|0|");
								p.CreatePacket(peer);
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopmoneybuy\n\n") {
							if (pInfo(peer)->offergems <= 0) break;
								if (pInfo(peer)->gtwl >= pInfo(peer)->offergems) {
									pInfo(peer)->gems += (pInfo(peer)->offergems * 2000);
									{
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("You got `0" + setGems(pInfo(peer)->offergems * 2000) + "`` Gems!");
										p.CreatePacket(peer);
									}
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									gamepacket_t p;
									p.Insert("OnSetBux");
									p.Insert(pInfo(peer)->gems);
									p.Insert(0);
									p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
									if (pInfo(peer)->supp >= 2) {
										p.Insert((float)33796, (float)1, (float)0);
									}
									p.CreatePacket(peer);
									pInfo(peer)->gtwl -= pInfo(peer)->offergems;
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|top\nbuttonClicked|yesterdaylist\n\n" || cch == "action|dialog_return\ndialog_name|top\nbuttonClicked|overalllist\n\n" || cch == "action|claimprogressbar\n" || cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoptitle\n\n" || cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopgrowtoken\n\n" || cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopxp\n\n" || cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprankvip\n\n" || cch == "action|dialog_return\ndialog_name|top\nbuttonClicked|toplist\n\n" || cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopmoney\n\n" || cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprankglory\n\n" || cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprankmod\n\n" || cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprank\n\n" || cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopitems\n\n" || cch == "action|dialog_return\ndialog_name|socialportal\nbuttonClicked|kitsystem\n\n" || cch == "action|dialog_return\ndialog_name|socialportal\nbuttonClicked|systemcoin\n\n") {
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								if (cch == "action|dialog_return\ndialog_name|top\nbuttonClicked|yesterdaylist\n\n")p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`5Top Worlds Of Yesterday``|left|394|\nadd_spacer|" + top_yesterday_list + "\nadd_button|wotwlistback|`oBack`|NOFLAGS|0|0|\nend_dialog|top|Close||\n");
								if (cch == "action|dialog_return\ndialog_name|top\nbuttonClicked|overalllist\n\n")p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Top Worlds Of All Time``|left|394|\nadd_spacer|" + top_overall_list + "\nadd_button|wotwlistback|`oBack`|NOFLAGS|0|0|\nend_dialog|top|Close||\n");
								if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprank\n\n") p.Insert(a + "set_default_color|`o\n\nadd_label_with_icon|big|`0Roles``|left|408|\n\nadd_spacer|small|\n\nadd_textbox|`rPlease choose item that you want to purchase!``|left|\n\nadd_spacer|small|\nadd_button_with_icon|" + (pInfo(peer)->glo ? "" : "shoprankglory") + "|`9Road to GLory`` `0(``" + (pInfo(peer)->glo ? "`2OWNED``" : "`9250Wls``") + "`0)``|noflags|9436|\nadd_button_with_icon|" + (pInfo(peer)->gp ? "" : "shoprankgrowpass") + "|`9Grow Pass`` `0(``" + (pInfo(peer)->gp ? "`2OWNED``" : "`91500Wls``") + "`0)``|noflags|11304|\nadd_button_with_icon|" + (pInfo(peer)->mod ? "" : "shoprankmod") + "|`bModerator`` `0(``" + (pInfo(peer)->mod ? "`2OWNED" : "`91500Wls``") + "`0)``|noflags|278|\nadd_button_with_icon|" + (pInfo(peer)->vip ? "" : "shoprankvip") + "|`eVIP`` `0(``" + (pInfo(peer)->vip ? "`2OWNED``" : "`9600Wls``") + "`0)``|noflags|276|"/*"\nadd_button_with_icon|shoprankgrowpass1|`rGrowPass LVL1`` `0(```9200Wls```0)``|noflags|9222|\nadd_button_with_icon|shoprankgrowpass2|`rGrowPass LVL2`` `0(```9400Wls```0)``|noflags|9222|\nadd_button_with_icon|shoprankgrowpass3|`rGrowPass LVL3`` `0(```9500Wls```0)``|noflags|9222|"*/"||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_button|shop|`0Back..``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|chc0|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoptitle\n\n") p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`2Purchase Title|left|9472|\n\nadd_spacer|small|\n\nadd_textbox|Choose which title do you want to purchase?|left|\nadd_smalltext|Note: We are only selling 5 titles for real growtopia payment.|left|\ntext_scaling_string|100,000,000,000coin|\nadd_spacer|small|\nadd_button_with_icon|" + string(pInfo(peer)->legend ? "" : "shoptit_leg") + "|`9Legendary`` `0(``" + (pInfo(peer)->legend ? "`2OWNED``" : "`91000WL``") + "`0)``|noflags|1794|\nadd_button_with_icon|" + string(pInfo(peer)->drtitle ? "" : "shoptit_doc") + "|`4Doctor`` `0(``" + (pInfo(peer)->drtitle ? "`2OWNED``" : "`9500WL``") + "`0)``|noflags|7068|\nadd_button_with_icon|" + string(pInfo(peer)->level >= 125 ? "" : "shoptit_125") + "|`3Blue Name`` `0(``" + (pInfo(peer)->level >= 125 ? "`2OWNED``" : "`9700WL``") + "`0)``|noflags|1488|\nadd_button_with_icon|" + (pInfo(peer)->have_master ? "" : "shoptit_men") + "|`8Mentor`` `0(``" + (pInfo(peer)->have_master ? "`2OWNED``" : "`9500WL``") + "`0)``|noflags|9472|\nadd_button_with_icon|" + (pInfo(peer)->have_donor ? "" : "shoptit_don") + "|`1G```24```6G`` `0(``" + (pInfo(peer)->have_donor ? "`2OWNED``" : "`9500WL``") + "`0)``|noflags|10856|\nadd_button_with_icon|" + (pInfo(peer)->unlockRoleSkin ? "" : "shoptit_skin") + "|`3Role Skin Name`` `0(``" + (pInfo(peer)->unlockRoleSkin ? "`2OWNED``" : "`9500WL``") + "`0)``|noflags|10856|\nadd_button_with_icon||END_LIST|noflags|0||\nadd_button|shop|`0Back``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|chc0|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopitems\n\n") p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Purchase items``|left|6312|\n\nadd_spacer|small|\n\nadd_textbox|`rPlease choose item that you want to purchase!``|left|\n\nadd_spacer|small|" + shop_list + "||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_button|shop|`0Back..``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|chc0|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								if (cch == "action|dialog_return\ndialog_name|socialportal\nbuttonClicked|kitsystem\n\n") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`2" + server_name + " Coin Shop``|left|9550|\nadd_spacer|small|\nadd_textbox|Claim the Coin on `2Growpedia`` for free if the level is right|left|\nadd_spacer|small|\nadd_textbox|You have `p" + setGems(pInfo(peer)->kit) + " Coin``.|left|\ntext_scaling_string|5,000kit|" + itsrkyy_kit + "||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nadd_textbox|`4NOTE`` : Coin Shop is entirely separate from regular xp...|left|\nadd_textbox|To get Coin exp You Can Claim On Growpedia Items. And you can do one of following activities|left|\nadd_textbox|- Smash Block (Big Rarity to boost like regular xp)|left|\nadd_textbox|- Harvest Trees|left|\nadd_textbox|- Harvest Providers|left|\nadd_textbox|- Use Experience Potion 100% Faster|left|\nadd_spacer|small|\nadd_button|chc0|Thanks For The Info!|noflags|0|0|\nnend_dialog|gazette||OK|");
								if (cch == "action|dialog_return\ndialog_name|socialportal\nbuttonClicked|systemcoin\n\n") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`2Market " + server_name + " Store``|left|752|\nadd_spacer|small|\nadd_textbox|Welcome to `2Market " + server_name + " Store``! Do you have any `2Dollar? `wYou can buy items from me with them.|left|\nadd_spacer|small|\nadd_textbox|You have `p" + setGems(pInfo(peer)->coin) + " $USD``.|left|\ntext_scaling_string|5,000coin|" + coin_list + "||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_button|chc0|OK|noflags|0|0|\nnend_dialog|gazette||OK|");
								if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprankmod\n\n")p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Purchase Moderator``|left|18|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `31500`` `9World Locks``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\n\nadd_textbox|`6Rules:``|left|\nadd_smalltext|`e1.`` `rDo not abuse your role.``|left|\nadd_smalltext|`e2.`` `rIf you are going to ban people, make sure to have screenshots/video for proof.``|left|\nadd_smalltext|`e3.`` `rSharing account will result in account loss.``|left|\nadd_smalltext|`e4.`` `rTrying to sell your account will result in ip-ban!``|left|\nadd_spacer|small|\n\nadd_textbox|`6Commands:``|left|\nadd_smalltext|`eAll commands are displayed in /help ``|left|\nadd_spacer|\nadd_url_button|comment|Purchase with E-Money|noflags|https://saweria.co/" + server_name + "|Open premium wls shop?|0|0|\nadd_button|shoprankmodbuy|`0Purchase for `91500 Wls``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|shop|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprankglory\n\n") p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Purchase Road to Glory``|left|18|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `3250`` `9World Locks``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\nadd_smalltext|Extra: `7RECEIVE INSTANTLY 100,000 GEMS - LEVEL UP & EARN UP TO 1,600,000 GEMS (save up 600+wls)``|left|\n\nadd_textbox|`6Rules:``|left|\nadd_smalltext|`e1.`` `rDo not abuse your role.``|left|\nadd_smalltext|`e2.`` `rIf you are going to ban people, make sure to have screenshots/video for proof.``|left|\nadd_smalltext|`e3.`` `rSharing account will result in account loss.``|left|\nadd_smalltext|`e4.`` `rTrying to sell your account will result in ip-ban!``|left|\nadd_spacer|small|\n\nadd_textbox|`6Commands:``|left|\nadd_smalltext|`eAll commands are displayed in /help ``|left|\nadd_spacer|\nadd_url_button|comment|Purchase with E-Money|noflags|https://saweria.co/" + server_name + "|Open premium wls shop?|0|0|\nadd_button|shoprankglorybuy|`0Purchase for `9250 Wls``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|shop|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopmoney\n\n")p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Gems``|left|112|\n\nadd_spacer|small|\nadd_textbox|`91 Wl is 2000 gems!``|\nadd_textbox|`9You have " + to_string(pInfo(peer)->gtwl) + " Wls, how much you want to spend wls for gems?`` `1(Enter Wls amount):``|\nadd_text_input|gemspurchase|Wls||30|\nend_dialog|shopgemsconfirm|Cancel|`5Check price..``|\n");
								if (cch == "action|dialog_return\ndialog_name|top\nbuttonClicked|toplist\n\n")p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`8Top worlds today``|left|394|\nadd_spacer|" + top_list + "\nadd_button|wotwlistback|`oBack`|NOFLAGS|0|0|\nend_dialog|top|Close||\n");
								if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprankvip\n\n") p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Purchase VIP``|left|18|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `3600`` `9World Locks``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\n\nadd_textbox|`6Rules:``|left|\nadd_smalltext|`e1.`` `rDo not spam with VIP SB.``|left|\nadd_smalltext|`e2.`` `rInpersonating someone with name changing will result in ban!``|left|\nadd_smalltext|`e3.`` `rSharing account will result in account loss.``|left|\nadd_smalltext|`e4.`` `rTrying to sell your account will result in ip-ban!``|left|\nadd_spacer|small|\n\nadd_textbox|`6Commands:``|left|\nadd_smalltext|`eAll commands are displayed in /vhelp (vip help)``|left|\nadd_spacer|\nadd_url_button|comment|Purchase with E-Money|noflags|https://saweria.co/" + server_name + "|Open premium wls shop?|0|0|\nadd_button|shoprankvipbuy|`0Purchase for `9600 Wls``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|shop|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopxp\n\n")p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`1Level``|left|1488|\nadd_spacer|small|\n\nadd_textbox|`1Choose which potion you want to purchase:``|left|\n\nadd_spacer|small|\nadd_button_with_icon|shopxp1|`01 Wls``|noflags|1488|100|\nadd_button_with_icon|shopxp2|`05 Wls``|noflags|1488|500|\nadd_button_with_icon|shopxp3|`010 Wls``|noflags|1488|1250|\nadd_button_with_icon||END_LIST|noflags|0||\n\nadd_spacer|\nadd_button|shop|`0Back..``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|chc0|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopgrowtoken\n\n")p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`1Purchase Growtoken``|left|1486|\nadd_spacer|small|\n\nadd_textbox|`1Choose which potion you want to purchase:``|left|\n\nadd_spacer|small|\nadd_button_with_icon|shopgt1|`0100 Wls``|noflags|1486|1|\nadd_button_with_icon|shopgt2|`0500 Wls``|noflags|1486|5|\nadd_button_with_icon|shopgt3|`01000 Wls``|noflags|1486|12|\nadd_button_with_icon||END_LIST|noflags|0||\n\nadd_spacer|\nadd_button|shop|`0Back..``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|chc0|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								if (cch == "action|claimprogressbar\n")p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wAbout Valentine's Event``|left|384|\nadd_spacer|small|\nadd_textbox|During Valentine's Week you will gain points for opening Golden Booty Chests. Claim enough points to earn bonus rewards.|left|\nadd_spacer|small|\nadd_textbox|Current Progress: " + to_string(pInfo(peer)->booty_broken) + "/100|left|\nadd_spacer|small|\nadd_textbox|Reward:|left|\nadd_label_with_icon|small|Super Golden Booty Chest|left|9350|\nadd_smalltext|             - 4x chance of getting a Golden Heart Crystal when opening!|left|\nend_dialog|valentines_quest||OK|\n");
									p.CreatePacket(peer);
								break;
							}//isskyy
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprankgrowpass\n\n" || cch == "action|shoprankgrowpass\n\n" || cch == "action|shoprankgrowpass\n" || cch == "action|shoprankgrowpass") {
								gamepacket_t p(500);
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Purchase Grow Pass``|left|18|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `31500`` `9World Locks``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\nadd_smalltext|Extra: `7Receive daily items everyday, get 2x coin points, receive newest coolest growotpia items, use /buy <item> command``|left|\n\nadd_textbox|`6Rules:``|left|\nadd_smalltext|`e1.`` `rDo not abuse your role.``|left|\nadd_smalltext|`e2.`` `rIf you are going to ban people, make sure to have screenshots/video for proof.``|left|\nadd_smalltext|`e3.`` `rSharing account will result in account loss.``|left|\nadd_smalltext|`e4.`` `rTrying to sell your account will result in ip-ban!``|left|\nadd_spacer|small|\n\nadd_textbox|`6Commands:``|left|\nadd_smalltext|`eAll commands are displayed in /help ``|left|\nadd_spacer|\nadd_url_button|comment|Purchase E-Money|noflags|https://saweria.co/" + server_name + "|Open premium wls shop?|0|0|\nadd_button|shoprankgrowpassbuy|`0Purchase for `91500 Wls``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|shop|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								p.CreatePacket(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|shop_price_") != string::npos) {
								int item = atoi(cch.substr(59, cch.length() - 59).c_str());
								if (item <= 0 || item >= items.size() || items[item].pwl == 0) continue;
								string special = "`eThere is none yet for that item``";
								if (item == 6312 || item == 11118) special = "`eGet `2Double Gems``";
								if (item == 11118) special += ", `220% higher chance of getting Magic Ores``";
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Purchase " + items[item].name + "``|left|" + to_string(items[item].id) + "|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `3" + setGems(items[item].pwl) + "`` `9World Locks``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\n\nadd_textbox|`6Special Effects:``|left|\nadd_smalltext|" + special + "|left|\nadd_spacer|\nadd_button|shop_item_" + to_string(item) + "|`0Purchase for `9" + setGems(items[item].pwl) + " Wls``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|shop|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								p.CreatePacket(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|shoptit_") != string::npos) {
								string kyy = cch.substr(56, cch.length() - 58).c_str();
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								if (kyy == "doc") p.Insert("set_default_color|`o\nadd_label_with_icon|big|Purchase Doctor Title|left|9472|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `3500`` `9World Locks``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\nadd_smalltext|Extra: `7[```4~```7]``|left|\nadd_spacer|\nadd_button|shopbuytit_" + kyy + "|`0Purchase for `9500 WL``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|shop|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								else if (kyy == "leg") p.Insert("set_default_color|`o\nadd_label_with_icon|big|Purchase Legendary Title|left|9472|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `31000`` `9World Locks``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\nadd_smalltext|Extra: `7[```4~```7]``|left|\nadd_spacer|\nadd_button|shopbuytit_" + kyy + "|`0Purchase for `91000 WL``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|shop|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								else if (kyy == "125") p.Insert("set_default_color|`o\nadd_label_with_icon|big|Purchase Blue Name|left|9472|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `3700`` `9World Locks``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\nadd_smalltext|Extra: `7[```4~```7]``|left|\nadd_spacer|\nadd_button|shopbuytit_" + kyy + "|`0Purchase for `9700 WL``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|shop|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								else if (kyy == "men") p.Insert("set_default_color|`o\nadd_label_with_icon|big|Purchase Mentor Title|left|9472|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `3500`` `9World Locks``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\nadd_smalltext|Extra: `7[```4~```7]``|left|\nadd_spacer|\nadd_button|shopbuytit_" + kyy + "|`0Purchase for `9500 WL``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|shop|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								else if (kyy == "don") p.Insert("set_default_color|`o\nadd_label_with_icon|big|Purchase Grow4Good Title|left|9472|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `3500`` `9World Locks``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\nadd_smalltext|Extra: `7[```4~```7]``|left|\nadd_spacer|\nadd_button|shopbuytit_" + kyy + "|`0Purchase for `9500 WL``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|shop|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								else if (kyy == "skin") p.Insert("set_default_color|`o\nadd_label_with_icon|big|Purchase Unlocked Skin Title|left|9472|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `3500`` `9World Locks``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\nadd_smalltext|Extra: `7[```4~```7]``|left|\nadd_spacer|\nadd_button|shopbuytit_" + kyy + "|`0Purchase for `9500 WL``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|shop|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								p.CreatePacket(peer);
								break;
								}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|shopbuytit_") != string::npos) {
									if (pInfo(peer)->world == "") break;
									string kyy = cch.substr(59, cch.length() - 61).c_str();
									int price = 0;
									if (kyy == "doc") price = 500;
									else if (kyy == "leg") price = 1000;
									else if (kyy == "125") price = 700;
									else if (kyy == "men") price = 500;
									else if (kyy == "don") price = 500;
									else if (kyy == "skin") price = 500;
									if (price != 0 && pInfo(peer)->gtwl >= price) {
										pInfo(peer)->gtwl -= price;
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										if (kyy == "doc") pInfo(peer)->drtitle = 1, pInfo(peer)->drt = 1, p.Insert(">> You've purchased Doctor Title");
										if (kyy == "leg") pInfo(peer)->legend = 1, pInfo(peer)->is_legend = 1, p.Insert(">> You've purchased Legendary Title");
										if (kyy == "125") pInfo(peer)->level = 125, pInfo(peer)->lvl125 = 1, p.Insert(">> You've purchased Blue Name");
										if (kyy == "men") pInfo(peer)->gp = 1, pInfo(peer)->gp = 1, p.Insert(">> You've purchased Mentor Title");
										if (kyy == "don") pInfo(peer)->gp = 1, pInfo(peer)->gp = 1, p.Insert(">> You've purchased Grow4Good Title");
										if (kyy == "skin") pInfo(peer)->unlockRoleSkin = 1, pInfo(peer)->titleDoctor = 1, pInfo(peer)->titleFisher = 1, pInfo(peer)->titleChef = 1, pInfo(peer)->titleStartopia = 1, p.Insert(">> You've purchased Role Skin Title");
										update_clothes(peer);
										p.CreatePacket(peer);
									}
									break;
									}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|lock_price_") != string::npos) {
								int item = atoi(cch.substr(59, cch.length() - 59).c_str());
								if (item <= 0 || item >= items.size() || items[item].gtwl == 0) continue;
								pInfo(peer)->lockeitem = item;
								int wl = 0, dl = 0;
								modify_inventory(peer, 242, wl);
								modify_inventory(peer, 1796, dl);
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`9Buy " + items[item].name + "?``|left|" + to_string(items[item].id) + "|\nadd_smalltext|`4" + items[item].description + "``|left|\nadd_smalltext|`1Price: " + (items[item].gtwl > 200 ? to_string(items[item].gtwl / 100) : to_string(items[item].gtwl)) + " " + (items[item].gtwl > 200 ? "Diamond Lock" : "World Locks") + "``|left|\nadd_spacer|\nadd_textbox|How many " + items[item].name + " do you want to buy, for " + (items[item].gtwl > 200 ? to_string(items[item].gtwl / 100) : to_string(items[item].gtwl)) + " " + (items[item].gtwl > 200 ? "Diamond Lock" : "World Locks") + " each?|left|\nadd_text_input|howmuch||1|5|\nadd_smalltext|" + (wl + dl != 0 ? "You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "" : "") + "|left|\nadd_button|lock_item_|`9Purchase``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|locke|No thanks|noflags|0|0|\nnend_dialog|gazette||OK|");
								p.CreatePacket(peer);
								}
								else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|locm_price_") != string::npos) {
								int item = atoi(cch.substr(59, cch.length() - 59).c_str());
								if (item <= 0 || item >= items.size() || items[item].u_gtwl == 0) continue;
								pInfo(peer)->lockeitem = item;
								int wl = 0, dl = 0;
								modify_inventory(peer, 242, wl);
								modify_inventory(peer, 1796, dl);
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`9Buy " + items[item].name + "?``|left|" + to_string(items[item].id) + "|\nadd_smalltext|`4" + items[item].description + "``|left|\nadd_smalltext|`1Price: "+setGems(items[item].u_gtwl) + " World Lock``|left|\nadd_spacer|\nadd_textbox|How many " + items[item].name + " do you want to buy, for " + (items[item].u_gtwl > 200 ? to_string(items[item].u_gtwl / 100) : to_string(items[item].u_gtwl)) + " " + (items[item].u_gtwl > 200 ? "Diamond Lock" : "World Locks") + " each?|left|\nadd_text_input|howmuch||1|5|\nadd_smalltext|" + (wl + dl != 0 ? "You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "" : "") + "|left|\nadd_button|lock_item_|`9Purchase``|noflags|0|0||small|\n\nadd_quick_exit|\nadd_button|lockm|No thanks|noflags|0|0|\nnend_dialog|gazette||OK|");
								p.CreatePacket(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|locke") != string::npos) {
								if (pInfo(peer)->world == "LOCKETOWN") {
									if (thedaytoday == 0 or thedaytoday == 1 or thedaytoday == 5 or thedaytoday == 6) {
										int wl = 0, dl = 0;
										modify_inventory(peer, 242, wl);
										modify_inventory(peer, 1796, dl);
										gamepacket_t p;
										p.Insert("OnDialogRequest");
										p.Insert(a + "set_default_color|`o\n\nadd_label_with_icon|big|`9Locke The Traveling Salesman``|left|4358|\nadd_spacer|small|\nadd_smalltext|Ho there, friend! Locke's my name, and locks are my game. I Love 'em all, Diamond, Huge.. even Small! If you can part with some locks, I'll give you something special in return. Whaddya say?|left|\nadd_spacer|small|\nadd_smalltext|" + (wl + dl != 0 ? "`9(Hmm, smells like you care carrying " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", and and " + to_string(dl) + " Diamond Lock" : "") + ")``" : "`9(Hmm, smells like you don't care any world locks)``") + "|left|\nadd_spacer|small|" + shop_list2 + "|\nadd_button|chc0|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
										p.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|lockm") != string::npos) {
								int wl = 0, dl = 0, bgl = 0;
								modify_inventory(peer, 242, wl);
								modify_inventory(peer, 1796, dl);
								modify_inventory(peer, 7188, bgl);
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert(a + "set_default_color|`o\n\nadd_label_with_icon|big|`9Sales-Man Untradeable``|left|2398|\nadd_spacer|small|\nadd_smalltext|Damn.. I hate LOCKE!! This guy takes all my diamond locks, i'm hungry so feed me more. The Untradeable Sales-Man|left|\nadd_spacer|small|\nadd_smalltext|" + (wl + dl != 0 ? "`9(Hmm, smells like you care carrying " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", and and " + to_string(dl) + " Diamond Lock" : "") + ")``" : "`9(Hmm, smells like you don't care any world locks)``") + "|left|" + (bgl == 0 ? "" : "\nadd_smalltext|`9(You are also holding additional " + to_string(bgl) + " Blue Gem Locks)``|left|") + "\nadd_spacer|small|" + shop_list2_2 + "|\nadd_button|chc0|Close|noflags|0|0|\nnend_dialog|gazette||OK|");
								p.CreatePacket(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|lock_item_\n\nhowmuch|") != string::npos) {
								if (pInfo(peer)->world == "LOCKETOWN") {
									int count = atoi(cch.substr(68, cch.length() - 68).c_str()), count2 = atoi(cch.substr(68, cch.length() - 68).c_str());
									if (count <= 0 || count > 200) continue;
									int item = pInfo(peer)->lockeitem;
									if (item <= 0 || item >= items.size()) continue;
									if (items[item].gtwl == 0 and items[item].u_gtwl == 0) continue;
									int allwl = 0, wl = 0, dl = 0, price = (items[item].gtwl == 0 ? items[item].u_gtwl : items[item].gtwl), priced = 0, bgl = 0;
									price *= count;
									priced = price;
									modify_inventory(peer, 242, wl);
									modify_inventory(peer, 1796, dl);
									modify_inventory(peer, 7188, bgl);
									allwl = wl + (dl * 100);
									int allbgl = bgl * 10000;
									if (allwl >= price || allbgl >= price && price > 20000) {
										int c_ = count;
										if (modify_inventory(peer, item, c_) == 0) {
											if (price <= 20000) {
												if (wl >= price) modify_inventory(peer, 242, price *= -1);
												else {
													modify_inventory(peer, 242, wl *= -1);
													modify_inventory(peer, 1796, dl *= -1);
													int givedl = (allwl - price) / 100;
													int givewl = (allwl - price) - (givedl * 100);
													modify_inventory(peer, 242, givewl);
													modify_inventory(peer, 1796, givedl);
												}
											}
											else {
												int removebgl = (price / 10000) * -1;
												modify_inventory(peer, 7188, removebgl);
											}
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world == pInfo(currentPeer)->world) {
													gamepacket_t p;
													p.Insert("OnConsoleMessage");
													p.Insert("`9[" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + " bought " + to_string(count2) + " " + items[item].name + " for " + to_string(priced) + " World Lock]");
													p.CreatePacket(currentPeer);
													packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
												}
											}
										}
										else {
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("No inventory space.");
											p.CreatePacket(peer);
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("`9You don't have enough wls!``");
										p.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|shop_item_") != string::npos) {
								int item = atoi(cch.substr(58, cch.length() - 58).c_str());
								if (item <= 0 || item >= items.size() || items[item].pwl == 0) continue;
								if (pInfo(peer)->gtwl >= items[item].pwl) {
									int c_ = 1;
									if (modify_inventory(peer, item, c_) == 0) {
										pInfo(peer)->gtwl -= items[item].pwl;
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("`o>> You purchased " + items[item].name + "!");
										p.CreatePacket(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No inventory space.");
										p.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|opop_price_") != string::npos) {
								int item = atoi(cch.substr(59, cch.length() - 59).c_str());
								if (item <= 0 || item >= items.size() || items[item].coins == 0) continue;
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Purchase " + items[item].name + "``|left|" + to_string(items[item].id) + "|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `3" + setGems(items[item].coins) + "`` `0coin``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\n\nadd_textbox|`6Other information:``|left|\nadd_smalltext|" + items[item].description + "|left|\nadd_spacer|\nadd_button|opop_item_" + to_string(item) + "|`0Purchase `9" + setGems(items[item].coins) + " coin``|noflags|0|0||small|\n\nadd_quick_exit|\nnend_dialog|gazette||OK|");
								p.CreatePacket(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|opop_item_") != string::npos) {
								int item = atoi(cch.substr(58, cch.length() - 58).c_str());
								if (item <= 0 || item >= items.size() || items[item].coins == 0) continue;
								if (pInfo(peer)->coin >= items[item].coins) {
									int c_ = 1;
									if (modify_inventory(peer, item, c_) == 0) {
										pInfo(peer)->coin -= items[item].coins;
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("`o>> You purchased " + items[item].name + "!");
										p.CreatePacket(peer);
									}
									if (item == 1486 && pInfo(peer)->quest_active && pInfo(peer)->quest_step == 6 && pInfo(peer)->quest_progress < 28) {
										pInfo(peer)->quest_progress++;
										if (pInfo(peer)->quest_progress >= 28) {
											pInfo(peer)->quest_progress = 28;
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("`9Legendary Quest step complete! I'm off to see a Wizard!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No inventory space.");
										p.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|kits_price_") != string::npos) {
								int item = atoi(cch.substr(59, cch.length() - 59).c_str());
								if (item <= 0 || item >= items.size() || items[item].kitne == 0) continue;
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`0Purchase " + items[item].name + "``|left|" + to_string(items[item].id) + "|\nadd_smalltext|`4Make sure to read this information clearly!``|left|\nadd_smalltext|Price: `3" + setGems(items[item].kitne) + "`` `0Kit``|left|\nadd_smalltext|Duration: `7[```4~```7]``|left|\nadd_smalltext|Stock: `7[```4~```7]``|left|\n\nadd_textbox|`6Other information:``|left|\nadd_smalltext|" + items[item].description + "|left|\nadd_spacer|\nadd_button|kits_item_" + to_string(item) + "|`0Purchase `9" + setGems(items[item].kitne) + " coin``|noflags|0|0||small|\n\nadd_quick_exit|\nnend_dialog|gazette||OK|");
								p.CreatePacket(peer);
								break;
								}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|kits_item_") != string::npos) {
								int item = atoi(cch.substr(58, cch.length() - 58).c_str());
								if (item <= 0 || item >= items.size() || items[item].kitne == 0) continue;
								if (pInfo(peer)->kit >= items[item].kitne) {
									int c_ = 1;
									if (modify_inventory(peer, item, c_) == 0) {
										pInfo(peer)->kit -= items[item].kitne;
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("`o>> You purchased " + items[item].name + "!");
										p.CreatePacket(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No inventory space.");
										p.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprankmodbuy\n\n") {
								if (pInfo(peer)->gtwl >= 1500) {
									pInfo(peer)->gtwl -= 1500;
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									pInfo(peer)->mod = 1;
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`o>> You purchased moderator! Type /help``");
									p.CreatePacket(peer);
									pInfo(peer)->name_color = (pInfo(peer)->dev == 1 ? royal_color : (pInfo(peer)->tmod == 1) ? mod_color : "`0");
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("`#**`` `$The Ancient Ones`` have `#made`` `w" + pInfo(peer)->tankIDName + "``->" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` a `bmoderator`` `#**`` (`2/deposit`` to purchase role!)");
										p.CreatePacket(currentPeer);
									}
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprankglorybuy\n\n") {
								if (pInfo(peer)->gtwl >= 250) {
									pInfo(peer)->gems += 100000;
									gamepacket_t p;
									p.Insert("OnSetBux");
									p.Insert(pInfo(peer)->gems);
									p.Insert(0);
									p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
									if (pInfo(peer)->supp >= 2) {
										p.Insert((float)33796, (float)1, (float)0);
									}
									p.CreatePacket(peer);
									pInfo(peer)->gtwl -= 250;
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									pInfo(peer)->glo = 1;
									{
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("`o>> You purchased Road to Glory! Wrench yourself and press on Road to Glory button!``");
										p.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprankgrowpassbuy\n\n") {
								if (pInfo(peer)->gtwl >= 1500) {
									pInfo(peer)->gtwl -= 1500;
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									pInfo(peer)->gp = 1;
									pInfo(peer)->gd = 0;
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`o>> You purchased Grow Pass! Wrench yourself to check the prizes``");
									p.CreatePacket(peer);
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shoprankvipbuy\n\n") {
								if (pInfo(peer)->gtwl >= 600) {
									pInfo(peer)->gtwl -= 600;
									pInfo(peer)->vip = 1;
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`o>> You purchased VIP! Type /vhelp``");
									p.CreatePacket(peer);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("`#**`` `$The Ancient Ones`` have `#made`` `w" + pInfo(peer)->tankIDName + "``->`e" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` a `bvip`` `#**`` (`2/deposit`` to purchase role!)");
										p.CreatePacket(currentPeer);
									}
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopxp1\n\n") {
								if (pInfo(peer)->gtwl >= 1) {
									pInfo(peer)->gtwl -= 1;
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									add_peer_xp(peer, 100);
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`o>> You purchased 100 XP!");
									p.CreatePacket(peer);
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopxp2\n\n") {
								if (pInfo(peer)->gtwl >= 5) {
									pInfo(peer)->gtwl -= 5;
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									add_peer_xp(peer, 500);
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`o>> You purchased 500 XP!");
									p.CreatePacket(peer);
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopxp3\n\n") {
								if (pInfo(peer)->gtwl >= 10) {
									pInfo(peer)->gtwl -= 10;
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									add_peer_xp(peer, 1250);
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`o>> You purchased 1250 XP!");
									p.CreatePacket(peer);
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopgt1\n\n") {
								if (pInfo(peer)->gtwl >= 100) {
									int count = 1;
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									if (modify_inventory(peer, 1486, count) == -1) p.Insert("No inventory space.");
									else {
										if (pInfo(peer)->gtwl >= 100) {
											pInfo(peer)->gtwl -= 100;
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("`o>> You purchased 1 Growtoken!");
											p.CreatePacket(peer);
										}
									}
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopgt1\n\n") {
								if (pInfo(peer)->gtwl >= 500) {
									int count = 5;
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									if (modify_inventory(peer, 1486, count) == -1) p.Insert("No inventory space.");
									else {
										if (pInfo(peer)->gtwl >= 500) {
											pInfo(peer)->gtwl -= 500;
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("`o>> You purchased 5 Growtoken!");
											p.CreatePacket(peer);
										}
									}
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shopgt3\n\n") {
								if (pInfo(peer)->gtwl >= 1000) {
									int count = 12;
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									if (modify_inventory(peer, 1486, count) == -1) p.Insert("No inventory space.");
									else {
										if (pInfo(peer)->gtwl >= 1000) {
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											pInfo(peer)->gtwl -= 1000;
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("`o>> You purchased 12 Growtoken!");
											p.CreatePacket(peer);
										}
									}
								}
								break;
							}
							else if (cch.find("action|showblarneyprogress") != string::npos) {
								gamepacket_t p(550);
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wBlarney Bonanza!``|left|528|\nadd_spacer|small|\nadd_textbox|Welcome to the Blarney Bonanza|left|\nadd_spacer|small|\nadd_textbox|As you, as a community, complete Blarneys and kiss the most magical stone, items will unlock for you to pick up in the store.|left|\nadd_spacer|small|\nadd_textbox|There are 4 items to unlock throughout the event.|left|\nadd_spacer|small|\nadd_textbox|Items will only remain unlocked for a short amount of time, so make sure you check back often! These items can be unlocked multiple times throughout the week.|left|\nadd_spacer|small|\nend_dialog|blarney_dialog||OK|\n");
								p.CreatePacket(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|adventure_reply\nbuttonClicked|button1\n\n") != string::npos) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator pa = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (pa != worlds.end()) {
								World* world_ = &worlds[pa - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert(a + "`2The door opens!" + (block_->destGate[0] == "" ? " But nothing is behind it." : "") + "``");
								string door_target = block_->destGate[0];
								string door_id = block_->destGateId[0];
								if (door_target != "") {
									gamepacket_t p3(0, pInfo(peer)->netID);
									p3.Insert("OnPlayPositioned");
									p3.Insert("audio/door_open.wav");
									p3.CreatePacket(peer);
									World target_world = worlds[pa - worlds.begin()];
									if (!door_target.empty() && door_target != world_->name) {
										if (!check_name(door_target)) {
											gamepacket_t p(250, pInfo(peer)->netID);
											p.Insert("OnSetFreezeState");
											p.Insert(1);
											p.CreatePacket(peer);
											{
												gamepacket_t p(250);
												p.Insert("OnConsoleMessage");
												p.Insert(door_target);
												p.CreatePacket(peer);
											}
											{
												gamepacket_t p(250);
												p.Insert("OnZoomCamera");
												p.Insert((float)10000.000000);
												p.Insert(1000);
												p.CreatePacket(peer);
											}
											{
												gamepacket_t p(250, pInfo(peer)->netID);
												p.Insert("OnSetFreezeState");
												p.Insert(0);
												p.CreatePacket(peer);
											}
											break;
										}
										target_world = get_world(door_target);
									}
									int spawn_x = 0, spawn_y = 0;
									int ySize = static_cast<int>(target_world.blocks.size()) / 100;
									int xSize = static_cast<int>(target_world.blocks.size()) / ySize;
									for (int i_ = 0; i_ < target_world.blocks.size(); i_++) {
										WorldBlock block_data = target_world.blocks[i_];
										if (block_data.fg == 1684 || items[block_data.fg].blockType == BlockTypes::DOOR || items[block_data.fg].blockType == BlockTypes::PORTAL) {
											if (block_data.door_id == door_id) {
												spawn_x = i_ % xSize;
												spawn_y = i_ / xSize;
												break;
											}
										}
									}
									join_world(peer, target_world.name, spawn_x, spawn_y, 250, false, true);
								}
								p.CreatePacket(peer);
							}

							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|adventure_reply\nbuttonClicked|button2\n\n") != string::npos) {
							string name_ = pInfo(peer)->world;
							
							vector<World>::iterator pa = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (pa != worlds.end()) {
								World* world_ = &worlds[pa - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								if (block_->fg == 1682) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
									p.Insert(a + "`2The door opens!" + (block_->destGate[1] == "" ? " But nothing is behind it." : "") + "``");
									string door_target = block_->destGate[1], door_id = block_->destGateId[1];
									if (door_target != "") {
										gamepacket_t p3(0, pInfo(peer)->netID);
										p3.Insert("OnPlayPositioned"), p3.Insert("audio/door_open.wav"), p3.CreatePacket(peer);
										World target_world = worlds[pa - worlds.begin()];
										if (not door_target.empty() and door_target != world_->name) {
											if (not check_name(door_target)) {
												gamepacket_t p(250, pInfo(peer)->netID);
												p.Insert("OnSetFreezeState");
												p.Insert(1);
												p.CreatePacket(peer);
												{
													gamepacket_t p(250);
													p.Insert("OnConsoleMessage");
													p.Insert(door_target);
													p.CreatePacket(peer);
												}
												{
													gamepacket_t p(250);
													p.Insert("OnZoomCamera");
													p.Insert((float)10000.000000);
													p.Insert(1000);
													p.CreatePacket(peer);
												}
												{
													gamepacket_t p(250, pInfo(peer)->netID);
													p.Insert("OnSetFreezeState");
													p.Insert(0);
													p.CreatePacket(peer);
												}
												break;
											}
											target_world = get_world(door_target);
										}
										int spawn_x = 0, spawn_y = 0;
										int ySize = (int)target_world.blocks.size() / 100, xSize = (int)target_world.blocks.size() / ySize;
										for (int i_ = 0; i_ < target_world.blocks.size(); i_++) {
											WorldBlock block_data = target_world.blocks[i_];
											if (block_data.fg == 1684 or items[block_data.fg].blockType == BlockTypes::DOOR or items[block_data.fg].blockType == BlockTypes::PORTAL) {
												if (block_data.door_id == door_id) {
													spawn_x = i_ % xSize, spawn_y = i_ / xSize;
													break;
												}
											}
										}
										join_world(peer, target_world.name, spawn_x, spawn_y, 250, false, true);

									}
									p.CreatePacket(peer);
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|adventure_reply\nbuttonClicked|button3\n\n") != string::npos) {
							string name_ = pInfo(peer)->world;
							
							vector<World>::iterator pa = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (pa != worlds.end()) {
								World* world_ = &worlds[pa - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								if (block_->fg == 1682) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
									p.Insert(a + "`2The door opens!" + (block_->destGate[2] == "" ? " But nothing is behind it." : "") + "``");
									string door_target = block_->destGate[2], door_id = block_->destGateId[2];
									if (door_target != "") {
										gamepacket_t p3(0, pInfo(peer)->netID);
										p3.Insert("OnPlayPositioned"), p3.Insert("audio/door_open.wav"), p3.CreatePacket(peer);
										
										World target_world = worlds[pa - worlds.begin()];
										if (not door_target.empty() and door_target != world_->name) {
											if (not check_name(door_target)) {
												gamepacket_t p(250, pInfo(peer)->netID);
												p.Insert("OnSetFreezeState");
												p.Insert(1);
												p.CreatePacket(peer);
												{
													gamepacket_t p(250);
													p.Insert("OnConsoleMessage");
													p.Insert(door_target);
													p.CreatePacket(peer);
												}
												{
													gamepacket_t p(250);
													p.Insert("OnZoomCamera");
													p.Insert((float)10000.000000);
													p.Insert(1000);
													p.CreatePacket(peer);
												}
												{
													gamepacket_t p(250, pInfo(peer)->netID);
													p.Insert("OnSetFreezeState");
													p.Insert(0);
													p.CreatePacket(peer);
												}
												break;
											}
											target_world = get_world(door_target);
										}
										int spawn_x = 0, spawn_y = 0;
										int ySize = (int)target_world.blocks.size() / 100, xSize = (int)target_world.blocks.size() / ySize;
										for (int i_ = 0; i_ < target_world.blocks.size(); i_++) {
											WorldBlock block_data = target_world.blocks[i_];

											if (block_data.fg == 1684 or items[block_data.fg].blockType == BlockTypes::DOOR or items[block_data.fg].blockType == BlockTypes::PORTAL) {
												if (block_data.door_id == door_id) {
													spawn_x = i_ % xSize, spawn_y = i_ / xSize;
													break;
												}
											}
										}
										join_world(peer, target_world.name, spawn_x, spawn_y, 250, false, true);

									}
									p.CreatePacket(peer);
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|adventure_reply\nbuttonClicked|button4\n\n") != string::npos) {
							string name_ = pInfo(peer)->world;
							
							vector<World>::iterator pa = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (pa != worlds.end()) {
								World* world_ = &worlds[pa - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								if (block_->fg == 1682) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
									p.Insert(a + "`2The door opens!" + (block_->destGate[3] == "" ? " But nothing is behind it." : "") + "``");
									string door_target = block_->destGate[3], door_id = block_->destGateId[3];
									if (door_target != "") {
										gamepacket_t p3(0, pInfo(peer)->netID);
										p3.Insert("OnPlayPositioned"), p3.Insert("audio/door_open.wav"), p3.CreatePacket(peer);
										World target_world = worlds[pa - worlds.begin()];
										if (not door_target.empty() and door_target != world_->name) {
											if (not check_name(door_target)) {
												gamepacket_t p(250, pInfo(peer)->netID);
												p.Insert("OnSetFreezeState");
												p.Insert(1);
												p.CreatePacket(peer);
												{
													gamepacket_t p(250);
													p.Insert("OnConsoleMessage");
													p.Insert(door_target);
													p.CreatePacket(peer);
												}
												{
													gamepacket_t p(250);
													p.Insert("OnZoomCamera");
													p.Insert((float)10000.000000);
													p.Insert(1000);
													p.CreatePacket(peer);
												}
												{
													gamepacket_t p(250, pInfo(peer)->netID);
													p.Insert("OnSetFreezeState");
													p.Insert(0);
													p.CreatePacket(peer);
												}
												break;
											}
											target_world = get_world(door_target);
										}
										int spawn_x = 0, spawn_y = 0;
										int ySize = (int)target_world.blocks.size() / 100, xSize = (int)target_world.blocks.size() / ySize;
										for (int i_ = 0; i_ < target_world.blocks.size(); i_++) {
											WorldBlock block_data = target_world.blocks[i_];

											if (block_data.fg == 1684 or items[block_data.fg].blockType == BlockTypes::DOOR or items[block_data.fg].blockType == BlockTypes::PORTAL) {
												if (block_data.door_id == door_id) {
													spawn_x = i_ % xSize, spawn_y = i_ / xSize;
													break;
												}
											}
										}
										join_world(peer, target_world.name, spawn_x, spawn_y, 250, false, true);

									}
									p.CreatePacket(peer);
								}
							}
							break;
						}						
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shop\n\n" || cch == "action|dialog_return\ndialog_name|\nbuttonClicked|deposit\n\n") {
							if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|shop\n\n") SendCmd(peer, "/asset", true);
							if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|deposit\n\n") SendCmd(peer, "/deposit", true);
							break;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|onlinebtn\n\n") {
								pInfo(peer)->on = true;
								pInfo(peer)->busy = false;
								pInfo(peer)->away = false;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|busybtn\n\n") {
								pInfo(peer)->on = false;
								pInfo(peer)->busy = true;
								pInfo(peer)->away = false;
							}
							else if (cch == "action|dialog_return\ndialog_name|\nbuttonClicked|awaybtn\n\n") {
								pInfo(peer)->on = false;
								pInfo(peer)->busy = false;
								pInfo(peer)->away = true;
							}
							else if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|claim_reward\n\n") {
								if (pInfo(peer)->gp == 1) {
									if (today_day != pInfo(peer)->gd) {
										vector<int> list2{ 1796, 10396, 11476, 9772, 10386, 722, 10826 };
										int receive = 1, item = list2[rand() % list2.size()], received = 1;
										if (item == 10386 || item == 722) receive = 20, received = 20;
										if (item == 10826)receive = 5, received = 5;
										if (modify_inventory(peer, item, receive) == 0) {
											pInfo(peer)->gd = today_day;
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9 >> You claimed your Grow Pass reward:");
												p.CreatePacket(peer);
											}
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("Given `0" + to_string(received) + " " + items[item].name + "``.");
												p.CreatePacket(peer);
											}
											PlayerMoving data_{};
											data_.packetType = 17;
											data_.netID = 48;
											data_.YSpeed = 48;
											data_.x = pInfo(peer)->x + 16;
											data_.y = pInfo(peer)->y + 16;
											BYTE* raw = packPlayerMoving(&data_);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(currentPeer)->world == pInfo(peer)->world) {
													send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												}
											}
											delete[] raw;
										}
										else {
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("Clean your inventory and try again!");
												p.CreatePacket(peer);
											}
										}
									}
									else {
										{
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("You already claimed your reward today!");
											p.CreatePacket(peer);
										}
									}
								}
								break;
							}
						else if (cch.find("action|dialog_return\ndialog_name|storageboxxtreme\nitemid|") != string::npos) {
							int item = atoi(cch.substr(57, cch.length() - 57).c_str());
							if (item <= 0 || item >= items.size()) break;
							if (pInfo(peer)->lastwrenchb != 4516 and items[item].untradeable == 1 or item == 1424) {
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You can't store Untradeable items there!"), p.CreatePacket(peer);
							}
							else if (pInfo(peer)->lastwrenchb == 4516 and items[item].untradeable == 0 or item == 18 || item == 32 || item == 6336 || item == 1424) {
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You can't store Tradeable items there!"), p.CreatePacket(peer);
							}
							else {
								int got = 0, receive = 0;
								modify_inventory(peer, item, got);
								if (got == 0) break;
								pInfo(peer)->lastchoosenitem = item;
								gamepacket_t p;
								p.Insert("OnDialogRequest"), p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + items[pInfo(peer)->lastwrenchb].name + "``|left|" + to_string(pInfo(peer)->lastwrenchb) + "|\nadd_textbox|You have " + to_string(got) + " " + items[item].name + ". How many to store?|left|\nadd_text_input|itemcount||" + to_string(got) + "|3|\nadd_spacer|small|\nadd_button|do_add|Store Items|noflags|0|0|\nend_dialog|storageboxxtreme|Cancel||\n"), p.CreatePacket(peer);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|storageboxxtreme\nbuttonClicked|itm") != string::npos) {
							int itemnr = atoi(cch.substr(67, cch.length() - 67).c_str()), itemcount = 0;
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								if (block_access(peer, world_, block_, false, true)) {
									for (int i_ = 0; i_ < world_->sbox1.size(); i_++) {
										if (world_->sbox1[i_].x == pInfo(peer)->lastwrenchx and world_->sbox1[i_].y == pInfo(peer)->lastwrenchy) {
											itemcount++;
											if (itemnr == itemcount) {
												pInfo(peer)->lastchoosennr = itemnr;
												gamepacket_t p;
												p.Insert("OnDialogRequest"), p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + items[pInfo(peer)->lastwrenchb].name + "``|left|" + to_string(pInfo(peer)->lastwrenchb) + "|\nadd_textbox|You have `w" + to_string(world_->sbox1[i_].count) + " " + items[world_->sbox1[i_].id].name + "`` stored.|left|\nadd_textbox|Withdraw how many?|left|\nadd_text_input|itemcount||" + to_string(world_->sbox1[i_].count) + "|3|\nadd_spacer|small|\nadd_button|do_take|Remove Items|noflags|0|0|\nadd_button|cancel|Back|noflags|0|0|\nend_dialog|storageboxxtreme|Exit||\n"), p.CreatePacket(peer);
											}
										}
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|donation_box_edit\nitemid|") != string::npos) {
								int item = atoi(cch.substr(58, cch.length() - 58).c_str()), got = 0;
								modify_inventory(peer, item, got);
								if (got == 0) break;
								if (items[item].untradeable == 1 || item == 1424 || items[item].blockType == BlockTypes::FISH) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("`7[```4You can't place that in the box, you need it!`7]``"), p.CreatePacket(peer);
								}
								else if (items[item].rarity == 1) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("`7[```4This box only accepts items rarity 2+ or greater`7]``"), p.CreatePacket(peer);
								}
								else {
									pInfo(peer)->lastchoosenitem = item;
									gamepacket_t p;
									p.Insert("OnDialogRequest"), p.Insert("set_default_color|`o\nadd_label_with_icon|big|" + items[item].name + "``|left|" + to_string(item) + "|\nadd_textbox|How many to put in the box as a gift? (Note: You will `4LOSE`` the items you give!)|left|\nadd_text_input|count|Count:|" + to_string(got) + "|5|\nadd_text_input|sign_text|Optional Note:||128|\nadd_spacer|small|\nadd_button|give|`4Give the item(s)``|noflags|0|0|\nadd_spacer|small|\nadd_button|cancel|`wCancel``|noflags|0|0|\nend_dialog|give_item|||\n");
									p.CreatePacket(peer);
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|donation_box_edit\nbuttonClicked|takeall\n") != string::npos) {
								bool took = false, fullinv = false;
								gamepacket_t p3;
								p3.Insert("OnTalkBubble"), p3.Insert(pInfo(peer)->netID);
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									if (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and not world_->owner_name.empty() and (!guild_access(peer, world_->guild_id) and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end())) break;
									WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
									if (!items[block_->fg].donation) break;
									for (int i_ = 0; i_ < block_->donates.size(); i_++) {
										int receive = block_->donates[i_].count;
										if (modify_inventory(peer, block_->donates[i_].item, block_->donates[i_].count) == 0) {
											took = true;
											gamepacket_t p;
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->ispatrol == false) continue;
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9[PATROL] `0" + pInfo(peer)->tankIDName + " `oreceive `0" + items[block_->donates[i_].item].name + " `o" + to_string(receive) + "x from `0" + block_->donates[i_].name + "`oin `9" + pInfo(peer)->world + "`o.");
												p.CreatePacket(currentPeer);
											}
											p.Insert("OnConsoleMessage");
											p.Insert("`7[``" + pInfo(peer)->tankIDName + " receives `5" + to_string(receive) + "`` `w" + items[block_->donates[i_].item].name + "`` from `w" + block_->donates[i_].name + "``, how nice!`7]``");
											block_->donates.erase(block_->donates.begin() + i_);
											i_--;
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												p.CreatePacket(currentPeer);
											}
										}
										else fullinv = true;
									}
									if (block_->donates.size() == 0) {
										WorldBlock block_ = world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
										PlayerMoving data_{};
										data_.packetType = 5, data_.punchX = pInfo(peer)->lastwrenchx, data_.punchY = pInfo(peer)->lastwrenchy, data_.characterState = 0x8;
										BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, &block_));
										BYTE* blc = raw + 56;
										form_visual(blc, block_, *world_, peer, false);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 112 + alloc_(world_, &block_), ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw, blc;
									}
								}
								if (fullinv) {
									p3.Insert("I don't have enough room in my backpack to get the item(s) from the box!");
									gamepacket_t p2;
									p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("`2(Couldn't get all of the gifts)``"), p2.CreatePacket(peer);
								}
								else if (took) p3.Insert("`2Box emptied.``");
								p3.CreatePacket(peer);
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|surge\n") {
								if (pInfo(peer)->lastwrenchb == 4296 || pInfo(peer)->lastwrenchb == 8558) {
									setstats(peer, rand() % 30, "", items[pInfo(peer)->lastwrenchb].name);
									pInfo(peer)->lastwrenchb = 0;
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|give_item\nbuttonClicked|give\n\ncount|") != string::npos) {
								if (items[pInfo(peer)->lastwrenchb].blockType != BlockTypes::DONATION) break;
								int count = atoi(cch.substr(69, cch.length() - 69).c_str()), got = 0;
								string text = cch.substr(80 + to_string(count).length(), cch.length() - 80 + to_string(count).length()).c_str();
								if (pInfo(peer)->lastchoosenitem <= 0 or pInfo(peer)->lastchoosenitem == NULL or pInfo(peer)->lastchoosenitem > items.size()) break;
								replace_str(text, "\n", "");
								modify_inventory(peer, pInfo(peer)->lastchoosenitem, got);
								if (text.size() > 128 || got <= 0 || count <= 0 || count > items.size()) break;
								if (count > got || items[pInfo(peer)->lastchoosenitem].untradeable == 1 || pInfo(peer)->lastchoosenitem == 1424 || items[pInfo(peer)->lastchoosenitem].blockType == BlockTypes::FISH) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									if (count > got) p.Insert("You don't have that to give!");
									else p.Insert("`7[```4You can't place that in the box, you need it!`7]``");
									p.CreatePacket(peer);
								}
								else {
									string name_ = pInfo(peer)->world;
									vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									if (p != worlds.end()) {
										World* world_ = &worlds[p - worlds.begin()];
										WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
										if (!items[block_->fg].donation) break;
										Donate donate_{};
										donate_.item = pInfo(peer)->lastchoosenitem, donate_.count = count, donate_.name = pInfo(peer)->tankIDName, donate_.text = text;
										block_->donates.push_back(donate_);
										{
											PlayerMoving data_{};
											data_.packetType = 5, data_.punchX = pInfo(peer)->lastwrenchx, data_.punchY = pInfo(peer)->lastwrenchy, data_.characterState = 0x8;
											BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, block_));
											BYTE* blc = raw + 56;
											block_->flags = (block_->flags & 0x00400000 ? block_->flags : block_->flags | 0x00400000);
											form_visual(blc, *block_, *world_, peer, false, true);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												send_raw(currentPeer, 4, raw, 112 + alloc_(world_, block_), ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw, blc;
										}
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											{
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("`7[```5[```w" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + "`` places `5" + to_string(count) + "`` `2" + items[pInfo(peer)->lastchoosenitem].name + "`` into the " + items[pInfo(peer)->lastwrenchb].name + "`5]```7]``");
												p.Insert(0);
												p.CreatePacket(currentPeer);
												packet_(currentPeer, "action|play_sfx\nfile|audio/page_turn.wav\ndelayMS|0");
											}
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`7[```5[```w" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + "`` places `5" + to_string(count) + "`` `2" + items[pInfo(peer)->lastchoosenitem].name + "`` into the " + items[pInfo(peer)->lastwrenchb].name + "`5]```7]``");
												p.CreatePacket(currentPeer);
											}
										}
										modify_inventory(peer, pInfo(peer)->lastchoosenitem, count *= -1);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|storageboxxtreme\nbuttonClicked|cancel") != string::npos) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								if (world_->owner_name == pInfo(peer)->tankIDName || pInfo(peer)->dev)load_storagebox(peer, world_, block_);
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|storageboxxtreme\nbuttonClicked|do_take\n\nitemcount|") != string::npos) {
							int itemnr = pInfo(peer)->lastchoosennr, countofremoval = atoi(cch.substr(83, cch.length() - 83).c_str()), removed = 0, itemcount = 0;
							removed = countofremoval;
							if (countofremoval <= 0) break;
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								if (block_access(peer, world_, block_, false, true)) {
									for (int i_ = 0; i_ < world_->sbox1.size(); i_++) {
										if (world_->sbox1[i_].x == pInfo(peer)->lastwrenchx and world_->sbox1[i_].y == pInfo(peer)->lastwrenchy) {
											itemcount++;
											if (itemnr == itemcount and countofremoval < world_->sbox1[i_].count) {
												if (world_->sbox1[i_].count <= 0) break;
												world_->sbox1[i_].count -= removed;
												if (modify_inventory(peer, world_->sbox1[i_].id, countofremoval) == 0) {
													gamepacket_t p, p2;
													p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("Removed `w" + to_string(removed) + " " + items[world_->sbox1[i_].id].name + "`` in " + items[pInfo(peer)->lastwrenchb].name + "."), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
													p2.Insert("OnConsoleMessage"), p2.Insert("Removed `w" + to_string(removed) + " " + items[world_->sbox1[i_].id].name + "`` in the " + items[pInfo(peer)->lastwrenchb].name + "."), p2.CreatePacket(peer);
													PlayerMoving data_{};
													data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16, data_.packetType = 19, data_.plantingTree = 500, data_.punchX = world_->sbox1[i_].id, data_.punchY = pInfo(peer)->netID;
													int32_t to_netid = pInfo(peer)->netID;
													BYTE* raw = packPlayerMoving(&data_);
													raw[3] = 5;
													memcpy(raw + 8, &to_netid, 4);
													send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
													delete[] raw;
													i_ = world_->sbox1.size();
												}
											}
											else if (itemnr == itemcount and world_->sbox1[i_].count == countofremoval) {
												if (world_->sbox1[i_].count <= 0) break;
												if (modify_inventory(peer, world_->sbox1[i_].id, countofremoval) == 0) {
													gamepacket_t p, p2;
													p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("Removed `w" + to_string(removed) + " " + items[world_->sbox1[i_].id].name + "`` in " + items[pInfo(peer)->lastwrenchb].name + "."), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
													p2.Insert("OnConsoleMessage"), p2.Insert("Removed `w" + to_string(removed) + " " + items[world_->sbox1[i_].id].name + "`` in the " + items[pInfo(peer)->lastwrenchb].name + "."), p2.CreatePacket(peer);
													PlayerMoving data_{};
													data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16;
													data_.packetType = 19, data_.plantingTree = 500;
													data_.punchX = world_->sbox1[i_].id, data_.punchY = pInfo(peer)->netID;
													int32_t to_netid = pInfo(peer)->netID;
													BYTE* raw = packPlayerMoving(&data_);
													raw[3] = 5;
													memcpy(raw + 8, &to_netid, 4);
													send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
													delete[] raw;
													world_->sbox1.erase(world_->sbox1.begin() + i_);
													i_ = world_->sbox1.size();
												}
											}
										}
									}
								}
							}
							break;
						}
						else if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|builder_reward\n\n" || cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|fishing_reward\n\n" || cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|geiger_reward\n\n" || cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|farmer_reward\n\n" || cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|provider_reward\n\n") {
								if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|farmer_reward\n\n") farmer_reward_show(peer);
								if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|provider_reward\n\n")provider_reward_show(peer);
								if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|geiger_reward\n\n") geiger_reward_show(peer);
								if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|fishing_reward\n\n") 	fishing_reward_show(peer);
								if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|builder_reward\n\n")	builder_reward_show(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|bouncer_dialog\nbuttonClicked|gems_") != string::npos) {
							int wl = 0, dl = 0;
							modify_inventory(peer, 242, wl);
							modify_inventory(peer, 1796, dl);
							DialogBuilder confirm;
							int itemChoosed = atoi(cch.substr(67, cch.length() - 67).c_str());
							switch (itemChoosed) {
							case 50000: {
								confirm.add_label_icon(true, 242, "`eBuy World Locks?``")
									.add_spacer(false)
									.add_textbox("How many World Locks do you want to buy, for 100.000 ė each?")
									.add_text_input(5, "how", "", "1")
									.add_smalltext("`9You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "<CR>You also have " + fixint(pInfo(peer)->gems) + " ė in your pocket.``")
									.add_spacer(false)
									.add_button("bouncer_gemsbuy", "`9Purchase``")
									.add_button("bouncer_backButton", "`wNo Thanks``")
									.embed_data(false, "gemsbuy", to_string(itemChoosed));
								break;
							}
							case 100000: {
								confirm.add_label_icon(true, 1796, "`eBuy Diamond Locks?``")
									.add_spacer(false)
									.add_textbox("How many Diamond Locks do you want to buy, for 200.000 ė each?")
									.add_text_input(5, "how", "", "1")
									.add_smalltext("`9You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "<CR>You also have " + fixint(pInfo(peer)->gems) + " ė in your pocket.``")
									.add_spacer(false)
									.add_button("bouncer_gemsbuy", "`9Purchase``")
									.add_button("bouncer_backButton", "`wNo Thanks``")
									.embed_data(false, "gemsbuy", to_string(itemChoosed));
								break;
							}
							case 250000: {
								confirm.add_label_icon(true, 10410, "`eBuy Legendary Locks?``")
									.add_spacer(false)
									.add_textbox("How many Legendary Locks do you want to buy, for 500.000 ė each?")
									.add_text_input(5, "how", "", "1")
									.add_smalltext("`9You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "<CR>You also have " + fixint(pInfo(peer)->gems) + " ė in your pocket.``")
									.add_spacer(false)
									.add_button("bouncer_gemsbuy", "`9Purchase``")
									.add_button("bouncer_backButton", "`wNo Thanks``")
									.embed_data(false, "gemsbuy", to_string(itemChoosed));
								break;
							}
							case 500000: {
								confirm.add_label_icon(true, 4802, "`eBuy Royal Locks?``")
									.add_spacer(false)
									.add_textbox("How many Royal Locks do you want to buy, for 1.000.000 ė each?")
									.add_text_input(5, "how", "", "1")
									.add_smalltext("`9You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "<CR>You also have " + fixint(pInfo(peer)->gems) + " ė in your pocket.``")
									.add_spacer(false)
									.add_button("bouncer_gemsbuy", "`9Purchase``")
									.add_button("bouncer_backButton", "`wNo Thanks``")
									.embed_data(false, "gemsbuy", to_string(itemChoosed));
								break;
							}
							case 1000000: {
								confirm.add_label_icon(true, 7188, "`eBuy Blue Gem Locks?``")
									.add_spacer(false)
									.add_textbox("How many Blue Gem Locks do you want to buy, for 2.000.000 ė each?")
									.add_text_input(5, "how", "", "1")
									.add_smalltext("`9You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "<CR>You also have " + fixint(pInfo(peer)->gems) + " ė in your pocket.``")
									.add_spacer(false)
									.add_button("bouncer_gemsbuy", "`9Purchase``")
									.add_button("bouncer_backButton", "`wNo Thanks``")
									.embed_data(false, "gemsbuy", to_string(itemChoosed));
								break;
							}
							case 50: {
								confirm.add_label_icon(true, 242, "`eBuy World Locks?``")
									.add_spacer(false)
									.add_textbox("How many World Locks do you want to buy, for 50 ā each?")
									.add_text_input(5, "how", "", "1")
									.add_smalltext("`9You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "<CR>You also have " + fixint(pInfo(peer)->gems) + " ė in your pocket.``")
									.add_spacer(false)
									.add_button("bouncer_gemsbuy", "`9Purchase``")
									.add_button("bouncer_backButton", "`wNo Thanks``")
									.embed_data(false, "gemsbuy", to_string(itemChoosed));
								break;
							}
							case 100: {
								confirm.add_label_icon(true, 1796, "`eBuy Diamond Locks?``")
									.add_spacer(false)
									.add_textbox("How many Diamond Locks do you want to buy, for 100 ā each?")
									.add_text_input(5, "how", "", "1")
									.add_smalltext("`9You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "<CR>You also have " + fixint(pInfo(peer)->gems) + " ė in your pocket.``")
									.add_spacer(false)
									.add_button("bouncer_gemsbuy", "`9Purchase``")
									.add_button("bouncer_backButton", "`wNo Thanks``")
									.embed_data(false, "gemsbuy", to_string(itemChoosed));
								break;
							}
							case 250: {
								confirm.add_label_icon(true, 10410, "`eBuy Legendary Locks?``")
									.add_spacer(false)
									.add_textbox("How many Legendary Locks do you want to buy, for 250 ā each?")
									.add_text_input(5, "how", "", "1")
									.add_smalltext("`9You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "<CR>You also have " + fixint(pInfo(peer)->gems) + " ė in your pocket.``")
									.add_spacer(false)
									.add_button("bouncer_gemsbuy", "`9Purchase``")
									.add_button("bouncer_backButton", "`wNo Thanks``")
									.embed_data(false, "gemsbuy", to_string(itemChoosed));
								break;
							}
							case 500: {
								confirm.add_label_icon(true, 4802, "`eBuy Royal Locks?``")
									.add_spacer(false)
									.add_textbox("How many Royal Locks do you want to buy, for 500 ā each?")
									.add_text_input(5, "how", "", "1")
									.add_smalltext("`9You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "<CR>You also have " + fixint(pInfo(peer)->gems) + " ė in your pocket.``")
									.add_spacer(false)
									.add_button("bouncer_gemsbuy", "`9Purchase``")
									.add_button("bouncer_backButton", "`wNo Thanks``")
									.embed_data(false, "gemsbuy", to_string(itemChoosed));
								break;
							}
							case 1000: {
								confirm.add_label_icon(true, 7188, "`eBuy Blue Gem Locks?``")
									.add_spacer(false)
									.add_textbox("How many Blue Gem Locks do you want to buy, for 1000 ā each?")
									.add_text_input(5, "how", "", "1")
									.add_smalltext("`9You have " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", " + to_string(dl) + " Diamond Lock." : ".") + "<CR>You also have " + fixint(pInfo(peer)->gems) + " ė in your pocket.``")
									.add_spacer(false)
									.add_button("bouncer_gemsbuy", "`9Purchase``")
									.add_button("bouncer_backButton", "`wNo Thanks``")
									.embed_data(false, "gemsbuy", to_string(itemChoosed));
								break;
							}
							default: break;
							}
							confirm.add_quick_exit();
							enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(confirm.to_string()).pack());
							break;
						}
						else if (cch.find("buttonClicked|bouncer_gemsbuy") != string::npos) {
							int addItem = 0, removeItem = 0, itemPrice = 0, totalPrice = 0, allwl = 0, wl = 0, dl = 0, cl = 0;
							int purchaseAmount = atoi(explode("\n", explode("how|", cch)[1])[0].c_str());
							if (purchaseAmount <= 0 || purchaseAmount > 200) continue;
							int itemKind = atoi(explode("\n", explode("gemsbuy|", cch)[1])[0].c_str());
							modify_inventory(peer, 242, wl);
							modify_inventory(peer, 1796, dl);
							modify_inventory(peer, 7188, cl);
							allwl = wl + (dl * 100);
							int allcl = cl * 10000;
							switch (itemKind) {
							case 50: {
								itemPrice = 50;
								totalPrice = itemPrice *= purchaseAmount;
								if (allwl >= totalPrice || allcl >= totalPrice && totalPrice > 20000) {
									int c_ = purchaseAmount;
									if (modify_inventory(peer, 242, c_) == 0) {
										if (totalPrice <= 20000) {
											if (wl >= totalPrice) modify_inventory(peer, 242, totalPrice *= -1);
											else {
												modify_inventory(peer, 242, wl *= -1);
												modify_inventory(peer, 1796, dl *= -1);
												int givedl = (allwl - totalPrice) / 100;
												int givewl = (allwl - totalPrice) - (givedl * 100);
												modify_inventory(peer, 242, givewl);
												modify_inventory(peer, 1796, givedl);
											}
										}
										else {
											int removebgl = (totalPrice / 10000) * -1;
											modify_inventory(peer, 7188, removebgl);
										}
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9[" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + " bought " + to_string(purchaseAmount) + " " + items[242].name + " for " + to_string(totalPrice) + " World Lock]");
												p.CreatePacket(currentPeer);
												packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
											}
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No inventory space.");
										p.CreatePacket(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`9You don't have enough wls!``");
									p.CreatePacket(peer);
								}
								break;
							}
							case 100: {
								itemPrice = 100;
								totalPrice = itemPrice *= purchaseAmount;
								if (allwl >= totalPrice || allcl >= totalPrice && totalPrice > 20000) {
									int c_ = purchaseAmount;
									if (modify_inventory(peer, 1796, c_) == 0) {
										if (totalPrice <= 20000) {
											if (wl >= totalPrice) modify_inventory(peer, 242, totalPrice *= -1);
											else {
												modify_inventory(peer, 242, wl *= -1);
												modify_inventory(peer, 1796, dl *= -1);
												int givedl = (allwl - totalPrice) / 100;
												int givewl = (allwl - totalPrice) - (givedl * 100);
												modify_inventory(peer, 242, givewl);
												modify_inventory(peer, 1796, givedl);
											}
										}
										else {
											int removebgl = (totalPrice / 10000) * -1;
											modify_inventory(peer, 7188, removebgl);
										}
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9[" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + " bought " + to_string(purchaseAmount) + " " + items[1796].name + " for " + to_string(totalPrice) + " World Lock]");
												p.CreatePacket(currentPeer);
												packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
											}
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No inventory space.");
										p.CreatePacket(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`9You don't have enough wls!``");
									p.CreatePacket(peer);
								}
								break;
							}
							case 250: {
								itemPrice = 250;
								totalPrice = itemPrice *= purchaseAmount;
								if (allwl >= totalPrice || allcl >= totalPrice && totalPrice > 20000) {
									int c_ = purchaseAmount;
									if (modify_inventory(peer, 10410, c_) == 0) {
										if (totalPrice <= 20000) {
											if (wl >= totalPrice) modify_inventory(peer, 242, totalPrice *= -1);
											else {
												modify_inventory(peer, 242, wl *= -1);
												modify_inventory(peer, 1796, dl *= -1);
												int givedl = (allwl - totalPrice) / 100;
												int givewl = (allwl - totalPrice) - (givedl * 100);
												modify_inventory(peer, 242, givewl);
												modify_inventory(peer, 1796, givedl);
											}
										}
										else {
											int removebgl = (totalPrice / 10000) * -1;
											modify_inventory(peer, 7188, removebgl);
										}
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9[" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + " bought " + to_string(purchaseAmount) + " " + items[10410].name + " for " + to_string(totalPrice) + " World Lock]");
												p.CreatePacket(currentPeer);
												packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
											}
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No inventory space.");
										p.CreatePacket(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`9You don't have enough wls!``");
									p.CreatePacket(peer);
								}
								break;
							}
							case 500: {
								itemPrice = 500;
								totalPrice = itemPrice *= purchaseAmount;
								if (allwl >= totalPrice || allcl >= totalPrice && totalPrice > 20000) {
									int c_ = purchaseAmount;
									if (modify_inventory(peer, 4802, c_) == 0) {
										if (totalPrice <= 20000) {
											if (wl >= totalPrice) modify_inventory(peer, 242, totalPrice *= -1);
											else {
												modify_inventory(peer, 242, wl *= -1);
												modify_inventory(peer, 1796, dl *= -1);
												int givedl = (allwl - totalPrice) / 100;
												int givewl = (allwl - totalPrice) - (givedl * 100);
												modify_inventory(peer, 242, givewl);
												modify_inventory(peer, 1796, givedl);
											}
										}
										else {
											int removebgl = (totalPrice / 10000) * -1;
											modify_inventory(peer, 7188, removebgl);
										}
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9[" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + " bought " + to_string(purchaseAmount) + " " + items[4802].name + " for " + to_string(totalPrice) + " World Lock]");
												p.CreatePacket(currentPeer);
												packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
											}
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No inventory space.");
										p.CreatePacket(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`9You don't have enough wls!``");
									p.CreatePacket(peer);
								}
								break;
							}
							case 1000: {
								itemPrice = 1000;
								totalPrice = itemPrice *= purchaseAmount;
								if (allwl >= totalPrice || allcl >= totalPrice && totalPrice > 20000) {
									int c_ = purchaseAmount;
									if (modify_inventory(peer, 7188, c_) == 0) {
										if (totalPrice <= 20000) {
											if (wl >= totalPrice) modify_inventory(peer, 242, totalPrice *= -1);
											else {
												modify_inventory(peer, 242, wl *= -1);
												modify_inventory(peer, 1796, dl *= -1);
												int givedl = (allwl - totalPrice) / 100;
												int givewl = (allwl - totalPrice) - (givedl * 100);
												modify_inventory(peer, 242, givewl);
												modify_inventory(peer, 1796, givedl);
											}
										}
										else {
											int removebgl = (totalPrice / 10000) * -1;
											modify_inventory(peer, 7188, removebgl);
										}
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9[" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + " bought " + to_string(purchaseAmount) + " " + items[7188].name + " for " + to_string(totalPrice) + " World Lock]");
												p.CreatePacket(currentPeer);
												packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
											}
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No inventory space.");
										p.CreatePacket(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`9You don't have enough wls!``");
									p.CreatePacket(peer);
								}
								break;
							}
							case 50000: {
								itemPrice = 100000;
								totalPrice = itemPrice *= purchaseAmount;
								if (pInfo(peer)->gems >= totalPrice) {
									int c_ = purchaseAmount;
									if (modify_inventory(peer, 242, c_) == 0) {
										{
											gamepacket_t p;
											p.Insert("OnSetBux"), p.Insert(pInfo(peer)->gems -= totalPrice), p.Insert(1), p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
											if (pInfo(peer)->supp >= 2) p.Insert((float)33796, (float)1, (float)0);
											p.CreatePacket(peer);
										}
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9[" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + " bought " + to_string(purchaseAmount) + " " + items[242].name + " for " + fixint(totalPrice) + " ė]");
												p.CreatePacket(currentPeer);
												packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
											}
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No Inventory Space");
										p.CreatePacket(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`9You don't have enough gems!``");
									p.CreatePacket(peer);
								}
								break;
							}
							case 100000: {
								itemPrice = 200000;
								totalPrice = itemPrice *= purchaseAmount;
								if (pInfo(peer)->gems >= totalPrice) {
									int c_ = purchaseAmount;
									if (modify_inventory(peer, 1796, c_) == 0) {
										{
											gamepacket_t p;
											p.Insert("OnSetBux"), p.Insert(pInfo(peer)->gems -= totalPrice), p.Insert(1), p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
											if (pInfo(peer)->supp >= 2) p.Insert((float)33796, (float)1, (float)0);
											p.CreatePacket(peer);
										}
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9[" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + " bought " + to_string(purchaseAmount) + " " + items[1796].name + " for " + fixint(totalPrice) + " ė]");
												p.CreatePacket(currentPeer);
												packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
											}
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No Inventory Space");
										p.CreatePacket(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`9You don't have enough gems!``");
									p.CreatePacket(peer);
								}
								break;
							}
							case 250000: {
								itemPrice = 500000;
								totalPrice = itemPrice *= purchaseAmount;
								if (pInfo(peer)->gems >= totalPrice) {
									int c_ = purchaseAmount;
									if (modify_inventory(peer, 10410, c_) == 0) {
										{
											gamepacket_t p;
											p.Insert("OnSetBux"), p.Insert(pInfo(peer)->gems -= totalPrice), p.Insert(1), p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
											if (pInfo(peer)->supp >= 2) p.Insert((float)33796, (float)1, (float)0);
											p.CreatePacket(peer);
										}
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9[" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + " bought " + to_string(purchaseAmount) + " " + items[10410].name + " for " + fixint(totalPrice) + " ė]");
												p.CreatePacket(currentPeer);
												packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
											}
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No Inventory Space");
										p.CreatePacket(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`9You don't have enough gems!``");
									p.CreatePacket(peer);
								}
								break;
							}
							case 500000: {
								itemPrice = 1000000;
								totalPrice = itemPrice *= purchaseAmount;
								if (pInfo(peer)->gems >= totalPrice) {
									int c_ = purchaseAmount;
									if (modify_inventory(peer, 4802, c_) == 0) {
										{
											gamepacket_t p;
											p.Insert("OnSetBux"), p.Insert(pInfo(peer)->gems -= totalPrice), p.Insert(1), p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
											if (pInfo(peer)->supp >= 2) p.Insert((float)33796, (float)1, (float)0);
											p.CreatePacket(peer);
										}
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9[" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + " bought " + to_string(purchaseAmount) + " " + items[4802].name + " for " + fixint(totalPrice) + " ė]");
												p.CreatePacket(currentPeer);
												packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
											}
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No Inventory Space");
										p.CreatePacket(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`9You don't have enough gems!``");
									p.CreatePacket(peer);
								}
								break;
							}
							case 1000000: {
								itemPrice = 2000000;
								totalPrice = itemPrice *= purchaseAmount;
								if (pInfo(peer)->gems >= totalPrice) {
									int c_ = purchaseAmount;
									if (modify_inventory(peer, 7188, c_) == 0) {
										{
											gamepacket_t p;
											p.Insert("OnSetBux"), p.Insert(pInfo(peer)->gems -= totalPrice), p.Insert(1), p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
											if (pInfo(peer)->supp >= 2) p.Insert((float)33796, (float)1, (float)0);
											p.CreatePacket(peer);
										}
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("`9[" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + " bought " + to_string(purchaseAmount) + " " + items[7188].name + " for " + fixint(totalPrice) + " ė]");
												p.CreatePacket(currentPeer);
												packet_(currentPeer, "action|play_sfx\nfile|audio/cash_register.wav\ndelayMS|0");
											}
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("No Inventory Space");
										p.CreatePacket(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`9You don't have enough gems!``");
									p.CreatePacket(peer);
								}
								break;
							}
							default: continue;
							}
							break;
						}
						else if (cch.find("buttonClicked|bouncer_backButton") != string::npos) {
							DialogBuilder bouncer;
							int wl = 0, dl = 0;
							int GemsPrice = 0, LockPrice = 0;
							modify_inventory(peer, 242, wl);
							modify_inventory(peer, 1796, dl);
							bouncer.add_label_icon(true, 12258, "The Bouncer")
								.add_smalltext("Ho there, friend! Bouncer's my name, and jewelry are my game. I Love 'em all, Gems even Locks! If you can part with some jewels, I'll give you something special in return. Whaddya say?")
								.add_smalltext("" + (wl + dl != 0 ? "`9Smells like you are carrying " + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? ", and " + to_string(dl) + " Diamond Lock" : "") + "``" : "`9Hmm, smells like you don't care any world locks``") + "")
								.add_smalltext("`9You've also got " + fixint(pInfo(peer)->gems) + " ė on your pocket``")
								.add_spacer(false)
								.add_label_icon(false, 9436, "Purchase with Gems");
							// The Bouncer List
							for (int i = 0; i < items.size(); i++) {
								if (i == 242) GemsPrice = 50000, bouncer.add_static_icon_button("gems_" + to_string(GemsPrice) + "", i, items[i].ori_name, "");
								if (i == 1796) GemsPrice = 100000, bouncer.add_static_icon_button("gems_" + to_string(GemsPrice) + "", i, items[i].ori_name, "");
								if (i == 10410) GemsPrice = 250000, bouncer.add_static_icon_button("gems_" + to_string(GemsPrice) + "", i, items[i].ori_name, "");
								if (i == 4802) GemsPrice = 500000, bouncer.add_static_icon_button("gems_" + to_string(GemsPrice) + "", i, items[i].ori_name, "");
								if (i == 7188) GemsPrice = 1000000, bouncer.add_static_icon_button("gems_" + to_string(GemsPrice) + "", i, items[i].ori_name, "");
							}
							bouncer.end_list()
								//.add_label_icon(false, 242, "Purchase with Locks");
							//for (int i = 0; i < items.size(); i++) {
								//if (i == 242) LockPrice = 50, bouncer.add_static_icon_button("gems_" + to_string(LockPrice) + "", i, items[i].ori_name, "");
								//if (i == 1796) LockPrice = 100, bouncer.add_static_icon_button("gems_" + to_string(LockPrice) + "", i, items[i].ori_name, "");
								//if (i == 10410) LockPrice = 250, bouncer.add_static_icon_button("gems_" + to_string(LockPrice) + "", i, items[i].ori_name, "");
								//if (i == 4802) LockPrice = 500, bouncer.add_static_icon_button("gems_" + to_string(LockPrice) + "", i, items[i].ori_name, "");
								//if (i == 7188) LockPrice = 1000, bouncer.add_static_icon_button("gems_" + to_string(LockPrice) + "", i, items[i].ori_name, "");
							//}
							// The end of Bouncer List
							//bouncer.end_list()
								.end_dialog("bouncer_dialog", "Exit", "");
							enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(bouncer.to_string()).pack());
							break;
						}
						if (cch.find("buttonClicked|cda_1") != string::npos) {
							c_daily(peer, true, "tab_1", 0);
						}
						if (cch.find("buttonClicked|cda_2") != string::npos) {
							c_daily(peer, true, "tab_2", 0);
						}
						else if (cch == "action|dialog_return\ndialog_name|backpack_menu\nbuttonClicked|backpack_upgrade\n\n") {
								if (pInfo(peer)->gems >= (1000 * ((pInfo(peer)->b_l * pInfo(peer)->b_l) + 25))*2) {
									if (pInfo(peer)->b_l * 10 > 200) {
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("You have reached max slots!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
									}
									else {
										pInfo(peer)->gems -= (1000 * ((pInfo(peer)->b_l * pInfo(peer)->b_l) + 25))*2;
										pInfo(peer)->b_l++;
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										gamepacket_t p;
										p.Insert("OnSetBux");
										p.Insert(pInfo(peer)->gems);
										p.Insert(0);
										p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
										if (pInfo(peer)->supp >= 2) {
											p.Insert((float)33796, (float)1, (float)0);
										}
										p.CreatePacket(peer);
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("Congratulations! You have upgraded your Backpack!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
										backpack_show(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("You don't have enough gems!");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(peer);
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|backpack_menu\nbuttonClicked|") != string::npos) {
								int choosen_item = atoi(cch.substr(61, cch.length() - 61).c_str());
								if (choosen_item >= pInfo(peer)->bp.size() || choosen_item > 200 || choosen_item > pInfo(peer)->b_l * 10) break;
								for (int i_ = 0; i_ < pInfo(peer)->bp.size(); i_++) {
									if (choosen_item == i_) {
										if (pInfo(peer)->bp[choosen_item].first <= 0 || pInfo(peer)->bp[choosen_item].first >= items.size()) break;
										int pickedup = pInfo(peer)->bp[choosen_item].second;
										if (modify_inventory(peer, pInfo(peer)->bp[choosen_item].first, pInfo(peer)->bp[choosen_item].second) == 0) {
											{
												gamepacket_t p, p2;
												p.Insert("OnConsoleMessage"), p.Insert("You picked up " + to_string(pickedup) + " " + items[pInfo(peer)->bp[choosen_item].first].name + "."), p.CreatePacket(peer);
												p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p.Insert("You picked up " + to_string(pickedup) + " " + items[pInfo(peer)->bp[choosen_item].first].name + "."), p2.CreatePacket(peer);
											}
											PlayerMoving data_{};
											data_.packetType = 19, data_.punchX = pInfo(peer)->bp[choosen_item].first, data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16;
											int32_t to_netid = pInfo(peer)->netID;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = 5;
											memcpy(raw + 8, &to_netid, 4);
											send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											delete[]raw;
											pInfo(peer)->bp.erase(pInfo(peer)->bp.begin() + i_);
										}
										else {
											gamepacket_t p;
											p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You don't have enough inventory space!"), p.CreatePacket(peer);
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|backpack_menu\nitemid|") != string::npos) {
								if (pInfo(peer)->bp.size() <= pInfo(peer)->b_l * 10) {
									int got = 0, item = atoi(cch.substr(54, cch.length() - 54).c_str());
									modify_inventory(peer, item, got);
									if (got <= 0) break;
									if (items[item].untradeable == 1 || item == 1424 || item == 5816 || items[item].blockType == BlockTypes::LOCK) {
										//|| items[item].blockType == BlockTypes::CONSUMABLE || items[item].blockType == BlockTypes::RANDOM_BLOCK || items[item].blockType == BlockTypes::BACKGROUND || items[item].blockType == BlockTypes::CLOTHING || items[item].blockType == BlockTypes::FOREGROUND || items[item].blockType == BlockTypes::SEED || items[item].blockType == BlockTypes::WEATHER || items[item].blockType == BlockTypes::BEDROCK) {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You can't store Untradeable items there!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
									}
									else {
										pInfo(peer)->bp.push_back(make_pair(item, got));
										modify_inventory(peer, item, got *= -1);
										PlayerMoving data_{};
										data_.packetType = 19, data_.punchX = item, data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16;
										int32_t to_netid = pInfo(peer)->netID;
										BYTE* raw = packPlayerMoving(&data_);
										raw[3] = 5;
										memcpy(raw + 8, &to_netid, 4);
										send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										delete[]raw;
										backpack_show(peer);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|dialog_eq_aura\nbutton_item_selection|") != string::npos) {
								int item = atoi(cch.substr(70, cch.length() - 70).c_str());
								if (item > 0 && item < items.size()) {
									if (items[item].toggleable) {
										pInfo(peer)->eq_a_1 = item;
										gamepacket_t p;
										p.Insert("OnDialogRequest");
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEQ Aura``|left|12634|\nadd_spacer|small|\nadd_textbox|Play music wherever you are with the EQ Aura! Choose a musical block from your inventory to play the song.|left|\nadd_spacer|small|" + (string(pInfo(peer)->eq_a_1 != 0 ? "\nadd_label_with_icon|small|`w" + items[pInfo(peer)->eq_a_1].name + "``|left|" + to_string(pInfo(peer)->eq_a_1) + "|\nadd_spacer|small|" : "")) + "\nadd_item_picker|button_item_selection|`wChange Block Item``|Choose Musical Block Item!|\nadd_button|restore_default|`wRemove Block Item``|noflags|0|0|\nadd_spacer|small|\nadd_spacer|small|\nend_dialog|dialog_eq_aura|Cancel|Update|\nadd_quick_exit|");
										p.CreatePacket(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnDialogRequest");
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEQ Aura``|left|12634|\nadd_spacer|small|\nadd_spacer|small|\nadd_textbox|`4Invalid item! You can only use musical block items! Please choose something else.``|left|\nadd_spacer|small|\nadd_textbox|Play music wherever you are with the EQ Aura! Choose a musical block from your inventory to play the song.|left|\nadd_spacer|small|" + (string(pInfo(peer)->eq_a != 0 ? "\nadd_label_with_icon|small|`w" + items[pInfo(peer)->eq_a].name + "``|left|" + to_string(pInfo(peer)->eq_a) + "|\nadd_spacer|small|" : "")) + "\nadd_item_picker|button_item_selection|`wChange Block Item``|Choose Musical Block Item!|\nadd_button|restore_default|`wRemove Block Item``|noflags|0|0|\nadd_spacer|small|\nadd_spacer|small|\nend_dialog|dialog_eq_aura|Cancel|Update|\nadd_quick_exit|");
										p.CreatePacket(peer);
									}
								}
								break;
						}
							else if (cch.find("action|dialog_return\ndialog_name|dialog_eq_aura\nbuttonClicked|restore_default") != string::npos) {
								pInfo(peer)->eq_a_1 = 0;
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wEQ Aura``|left|12634|\nadd_spacer|small|\nadd_textbox|Play music wherever you are with the EQ Aura! Choose a musical block from your inventory to play the song.|left|\nadd_spacer|small|" + (string(pInfo(peer)->eq_a_1 != 0 ? "\nadd_label_with_icon|small|`w" + items[pInfo(peer)->eq_a_1].name + "``|left|" + to_string(pInfo(peer)->eq_a_1) + "|\nadd_spacer|small|" : "")) + "\nadd_item_picker|button_item_selection|`wChange Block Item``|Choose Musical Block Item!|\nadd_button|restore_default|`wRemove Block Item``|noflags|0|0|\nadd_spacer|small|\nadd_spacer|small|\nend_dialog|dialog_eq_aura|Cancel|Update|\nadd_quick_exit|");
								p.CreatePacket(peer);
								break;
						}
							else if (cch.find("action|dialog_return\ndialog_name|dialog_eq_aura") != string::npos) {
								if (pInfo(peer)->eq_a_1 != 0 && !pInfo(peer)->eq_a_update) pInfo(peer)->eq_a = pInfo(peer)->eq_a_1, pInfo(peer)->eq_a_update = true;
								if (pInfo(peer)->eq_a_1 == 0) pInfo(peer)->eq_a_1 = 0, pInfo(peer)->eq_a = 0;
								update_clothes(peer);
								break;
						}
							else if (cch.find("action|dialog_return\ndialog_name|\nbuttonClicked|trans_") != string::npos) {
								int item = atoi(cch.substr(54, cch.length() - 54).c_str());
								if (item <= 0 || item >= items.size()) break;
								if (item == 256) {
									gamepacket_t p(0, pInfo(peer)->netID);
									p.Insert("OnFlagMay2019"), p.Insert(256);
									pInfo(peer)->flagmay = 256;
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
										if (pInfo(peer)->world == pInfo(currentPeer)->world) p.CreatePacket(currentPeer);
									}
								}
								int got = 0;
								modify_inventory(peer, item, got);
								if (got == 0) break;
								if (items[item].flagmay == 256) break;
								gamepacket_t p(0, pInfo(peer)->netID);
								pInfo(peer)->flagmay = items[item].flagmay;
								p.Insert("OnFlagMay2019"), p.Insert(items[item].flagmay);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
									if (pInfo(peer)->world == pInfo(currentPeer)->world) p.CreatePacket(currentPeer);
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|t_claimreward") != string::npos) {
								int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
								vector<int> list{ 98, 228, 1746, 1778, 1830, 5078, 1966, 6948, 6946, 4956 };
								if (reward <= 0 || reward > list.size()) break;
								if (list[reward - 1] == 228 || list[reward - 1] == 1746 || list[reward - 1] == 1778) count = 200;
								if (find(pInfo(peer)->t_p.begin(), pInfo(peer)->t_p.end(), lvl = reward * 5) == pInfo(peer)->t_p.end()) {
									if (pInfo(peer)->t_lvl >= lvl) {
										if (modify_inventory(peer, list[reward - 1], count) == 0) {
											pInfo(peer)->t_p.push_back(lvl);
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											{
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("Congratulations! You have received your Farmer Reward!");
												p.Insert(0), p.Insert(0);
												p.CreatePacket(peer);
											}
											PlayerMoving data_{};
											data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
											BYTE* raw = packPlayerMoving(&data_);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw;
											{
												PlayerMoving data_{};
												data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
												int32_t to_netid = pInfo(peer)->netID;
												BYTE* raw = packPlayerMoving(&data_);
												raw[3] = 5;
												memcpy(raw + 8, &to_netid, 4);
												send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												delete[] raw;
											}
											farmer_reward_show(peer);
										}
										else {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("You have full inventory space!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
									}
								}
								break;
							}
						else if (cch.find("action|dialog_return\ndialog_name|view_inventory\nbuttonClicked|") != string::npos) {
							if (pInfo(peer)->owner) {
								int item = atoi(cch.substr(62, cch.length() - 62).c_str()), got = 0;
								pInfo(peer)->choosenitem = item;
								if (item <= 0 || item > items.size()) break;
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
										modify_inventory(currentPeer, pInfo(peer)->choosenitem, got);
										gamepacket_t p;
										p.Insert("OnDialogRequest");
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Take`` `w" + items[pInfo(peer)->choosenitem].name + " from`` `#" + pInfo(currentPeer)->tankIDName + "``|left|" + to_string(pInfo(peer)->choosenitem) + "|\nadd_textbox|How many to `4take``? (player has " + to_string(got) + ")|left|\nadd_text_input|count||" + to_string(got) + "|5|\nend_dialog|take_item|Cancel|OK|");
										p.CreatePacket(peer);
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|take_item\ncount|") != string::npos) {
							if (pInfo(peer)->superdev) {
								int count = atoi(cch.substr(49, cch.length() - 49).c_str()), receive = atoi(cch.substr(49, cch.length() - 49).c_str());
								int remove = count * -1;
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
										if (count <= 0 || count > 200) break;
										if (modify_inventory(peer, pInfo(peer)->choosenitem, count) == 0) {
											int total = 0;
											modify_inventory(currentPeer, pInfo(peer)->choosenitem, total += remove);
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("Collected `w" + to_string(receive) + " " + items[pInfo(peer)->choosenitem].name + "``." + (items[pInfo(peer)->choosenitem].rarity > 363 ? "" : " Rarity: `w" + to_string(items[pInfo(peer)->choosenitem].rarity) + "``") + "");
											p.CreatePacket(peer);
										}
									}
								}
							}
							break;
						}						
							else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|p_claimreward") != string::npos) {
								int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
								vector<int> list{ 1008,1044,872,10450,870,5084,876,6950,6952,1674 };
								if (reward <= 0 || reward > list.size()) break;
								if (list[reward - 1] == 1008) count = 5;
								if (list[reward - 1] == 1044) count = 50;
								if (list[reward - 1] == 872) count = 200;
								if (list[reward - 1] == 10450) count = 3;
								if (find(pInfo(peer)->p_p.begin(), pInfo(peer)->p_p.end(), lvl = reward * 5) == pInfo(peer)->p_p.end()) {
									if (pInfo(peer)->p_lvl >= lvl) {
										if (modify_inventory(peer, list[reward - 1], count) == 0) {
											pInfo(peer)->p_p.push_back(lvl);
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											{
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("Congratulations! You have received your Provider Reward!");
												p.Insert(0), p.Insert(0);
												p.CreatePacket(peer);
											}
											PlayerMoving data_{};
											data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
											BYTE* raw = packPlayerMoving(&data_);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw;
											{
												PlayerMoving data_{};
												data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
												int32_t to_netid = pInfo(peer)->netID;
												BYTE* raw = packPlayerMoving(&data_);
												raw[3] = 5;
												memcpy(raw + 8, &to_netid, 4);
												send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												delete[] raw;
											}
											provider_reward_show(peer);
										}
										else {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("You have full inventory space!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|g_claimreward") != string::npos) {
							int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
							vector<int> list{ 4654,262,826,828,9712,3146,2266,5072,5070,9716 };
							if (reward <= 0 || reward > list.size()) break;
							if (list[reward - 1] == 262 || list[reward - 1] == 826 || list[reward - 1] == 828) count = 50;
							if (list[reward - 1] == 3146) count = 10;
							if (find(pInfo(peer)->g_p.begin(), pInfo(peer)->g_p.end(), lvl = reward * 5) == pInfo(peer)->g_p.end()) {
								if (pInfo(peer)->g_lvl >= lvl) {
									if (modify_inventory(peer, list[reward - 1], count) == 0) {
										pInfo(peer)->g_p.push_back(lvl);
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("Congratulations! You have received your Geiger Hunting Reward!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
										BYTE* raw = packPlayerMoving(&data_);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw;
										{
											PlayerMoving data_{};
											data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
											int32_t to_netid = pInfo(peer)->netID;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = 5;
											memcpy(raw + 8, &to_netid, 4);
											send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											delete[] raw;
										}
										geiger_reward_show(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You have full inventory space!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
									}
								}
							}
							break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|f_claimreward") != string::npos) {
							int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
							vector<int> list{ 3010, 3018, 3020, 3044, 5740, 3042, 3098, 3100, 3040, 10262 };
							if (reward <= 0 || reward > list.size()) break;
							if (list[reward - 1] == 3018) count = 200;
							if (list[reward - 1] == 3020 || list[reward - 1] == 3098) count = 50;
							if (list[reward - 1] == 3044) count = 25;
							if (find(pInfo(peer)->ff_p.begin(), pInfo(peer)->ff_p.end(), lvl = reward * 5) == pInfo(peer)->ff_p.end()) {
								if (pInfo(peer)->ff_lvl >= lvl) {
									if (modify_inventory(peer, list[reward - 1], count) == 0) {
										pInfo(peer)->ff_p.push_back(lvl);
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("Congratulations! You have received your Fishing Reward!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
										BYTE* raw = packPlayerMoving(&data_);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw;
										{
											PlayerMoving data_{};
											data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
											int32_t to_netid = pInfo(peer)->netID;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = 5;
											memcpy(raw + 8, &to_netid, 4);
											send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											delete[] raw;
										}
										fishing_reward_show(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTalkBubble");
										p.Insert(pInfo(peer)->netID);
										p.Insert("You have full inventory space!");
										p.Insert(0), p.Insert(0);
										p.CreatePacket(peer);
									}
								}
							}
							break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|roadtoglory\nbuttonClicked|claimreward") != string::npos) {
								int count = atoi(cch.substr(70, cch.length() - 70).c_str());
								if (count < 1 || count >10) break;
								if (std::find(pInfo(peer)->glo_p.begin(), pInfo(peer)->glo_p.end(), count) == pInfo(peer)->glo_p.end()) {
									if (pInfo(peer)->level >= count * 10) {
										pInfo(peer)->glo_p.push_back(count);
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										gamepacket_t p;
										p.Insert("OnSetBux");
										p.Insert(pInfo(peer)->gems += count * 100000);
										p.Insert(0);
										p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
										if (pInfo(peer)->supp >= 2) {
											p.Insert((float)33796, (float)1, (float)0);
										}
										p.CreatePacket(peer);
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("Congratulations! You have received your Road to Glory Reward!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
										BYTE* raw = packPlayerMoving(&data_);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw;
										glory_show(peer);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|bulletin_edit\nbuttonClicked|clear\n") != string::npos) {
								{
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(items[pInfo(peer)->lastwrenchb].blockType == BlockTypes::MAILBOX ? "`2Mailbox emptied.``" : "`2Text cleared.``"), p.Insert(0), p.Insert(0), p.CreatePacket(peer);
								}
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									for (int i_ = 0; i_ < world_->bulletin.size(); i_++) {
										if (world_->bulletin[i_].x == pInfo(peer)->lastwrenchx and world_->bulletin[i_].y == pInfo(peer)->lastwrenchy) {
											world_->bulletin.erase(world_->bulletin.begin() + i_);
											i_--;
										}
									}
									if (items[pInfo(peer)->lastwrenchb].blockType == BlockTypes::MAILBOX) {
										WorldBlock block_ = world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
										PlayerMoving data_{};
										data_.packetType = 5, data_.punchX = pInfo(peer)->lastwrenchx, data_.punchY = pInfo(peer)->lastwrenchy, data_.characterState = 0x8;
										BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, &block_));
										BYTE* blc = raw + 56;
										form_visual(blc, block_, *world_, peer, false);
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
											send_raw(currentPeer, 4, raw, 112 + alloc_(world_, &block_), ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw, blc;
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|textSpammer") != string::npos) {

								string text = explode("\n", explode("textBot|", cch)[1])[0];
								if (text.length() > 120) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
									p.Insert("`wText Spam Max 120 Characters.");
									p.Insert(0), p.Insert(1), p.CreatePacket(peer);
									break;
								}
								else if (text.length() < 1) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
									p.Insert("`wText Spam Min 1 Characters.");
									p.Insert(0), p.Insert(1), p.CreatePacket(peer);
									pInfo(peer)->npc_text = "";
									break;
								}
								pInfo(peer)->npc_text = text;
								gamepacket_t p;
								p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
								p.Insert("`wSetting Updated.");
								p.Insert(0), p.Insert(1), p.CreatePacket(peer);

					}
							else if (cch.find("action|dialog_return\ndialog_name|botSpammer\n") != string::npos) {
								if (cch.find("buttonClicked|positionBot") != string::npos) {
									pInfo(peer)->x_npc = pInfo(peer)->x;
									pInfo(peer)->y_npc = pInfo(peer)->y;
									pInfo(peer)->npc_summon = true;
									pInfo(peer)->npc_netID = (pInfo(peer)->netID + 999);
									pInfo(peer)->npc_name = "" + pInfo(peer)->tankIDName + " Bot `2Spamming";
									pInfo(peer)->npc_world = pInfo(peer)->world;
									gamepacket_t pSpawn(500), p2(500);

									p2.Insert("OnTalkBubble");
									p2.Insert(pInfo(peer)->netID);
									p2.Insert("Success Summon NPC Bot Spammer!!");
									p2.Insert(0), p2.Insert(0);
									p2.CreatePacket(peer);

									pSpawn.Insert("OnSpawn"), pSpawn.Insert("spawn|avatar\nnetID|" + to_string(pInfo(peer)->netID + 999) + "\nuserID|-1\ncolrect|0|0|20|30\nposXY|" + to_string((pInfo(peer))->x) + "|" + to_string((pInfo(peer))->y) + "\nname|``" + pInfo(peer)->tankIDName + " Bot `2Spamming``\ncountry|gb\ninvis|0\nmstate|0\nsmstate|0\nonlineID|");

									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED || currentPeer->data == NULL) continue;
										if (pInfo(peer)->world == pInfo(currentPeer)->world) {
											pSpawn.CreatePacket(currentPeer);
										}
									}
								}
								else if (cch.find("buttonClicked|botdev") != string::npos) {
									pInfo(peer)->x_npc = 83, pInfo(peer)->y_npc = 36;
									pInfo(peer)->npc_world = "";
									pInfo(peer)->npc_netID = 3;
									pInfo(peer)->npc_summon = false;
									{
										pInfo(peer)->x_npc = pInfo(peer)->x;
										pInfo(peer)->y_npc = pInfo(peer)->y;
										pInfo(peer)->npc_summon = true;
										pInfo(peer)->npc_netID = (pInfo(peer)->netID + 999);
										pInfo(peer)->npc_name = "" + pInfo(peer)->tankIDName + " Bot `2Spamming";
										pInfo(peer)->npc_world = pInfo(peer)->world;

										gamepacket_t pSpawn(500), p2(500);

										p2.Insert("OnTalkBubble");
										p2.Insert(pInfo(peer)->netID);
										p2.Insert("Success Change Position NPC Bot Spammer!!");
										p2.Insert(0), p2.Insert(0);
										p2.CreatePacket(peer);

										pSpawn.Insert("OnSpawn"), pSpawn.Insert("spawn|avatar\nnetID|" + to_string(pInfo(peer)->netID + 999) + "\nuserID|-1\ncolrect|0|0|20|30\nposXY|" + to_string((pInfo(peer))->x_npc) + "|" + to_string((pInfo(peer))->y_npc) + "\nname|``" + pInfo(peer)->tankIDName + " Bot `2Spamming``\ncountry|gb\ninvis|0\nmstate|0\nsmstate|0\nonlineID|");

										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED || currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												pSpawn.CreatePacket(currentPeer);
											}
										}
									}
								}
								else if (cch.find("buttonClicked|deleteText") != string::npos) {
									gamepacket_t p2;
									p2.Insert("OnTalkBubble");
									p2.Insert(pInfo(peer)->netID);
									p2.Insert("Success Delete Text NPC Bot Spammer!!");
									p2.Insert(0), p2.Insert(0);
									p2.CreatePacket(peer);
									pInfo(peer)->npc_text = "";
								}
								else if (cch.find("buttonClicked|changeBot") != string::npos) {
									gamepacket_t p2;
									p2.Insert("OnRemove");
									p2.Insert("netID|" + to_string(pInfo(peer)->npc_netID) + "\n");

									gamepacket_t p;
									p.Insert("OnRemove");
									p.Insert("netID|" + to_string(pInfo(peer)->npc_netID) + "\n");
									p.CreatePacket(peer);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED || currentPeer->data == NULL) continue;
										if (pInfo(peer)->npc_world != pInfo(currentPeer)->world) continue;
										p2.CreatePacket(currentPeer);
									}
									pInfo(peer)->x_npc = 0, pInfo(peer)->y_npc = 0;
									pInfo(peer)->npc_world = "";
									pInfo(peer)->npc_netID = 0;
									pInfo(peer)->npc_summon = false;
									{
										pInfo(peer)->x_npc = pInfo(peer)->x;
										pInfo(peer)->y_npc = pInfo(peer)->y;
										pInfo(peer)->npc_summon = true;
										pInfo(peer)->npc_netID = (pInfo(peer)->netID + 999);
										pInfo(peer)->npc_name = "" + pInfo(peer)->tankIDName + " Bot `2Spamming";
										pInfo(peer)->npc_world = pInfo(peer)->world;

										gamepacket_t pSpawn(500), p2(500);

										p2.Insert("OnTalkBubble");
										p2.Insert(pInfo(peer)->netID);
										p2.Insert("Success Change Position NPC Bot Spammer!!");
										p2.Insert(0), p2.Insert(0);
										p2.CreatePacket(peer);

										pSpawn.Insert("OnSpawn"), pSpawn.Insert("spawn|avatar\nnetID|" + to_string(pInfo(peer)->netID + 999) + "\nuserID|-1\ncolrect|0|0|20|30\nposXY|" + to_string((pInfo(peer))->x) + "|" + to_string((pInfo(peer))->y) + "\nname|``" + pInfo(peer)->tankIDName + " Bot `2Spamming``\ncountry|gb\ninvis|0\nmstate|0\nsmstate|0\nonlineID|");

										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED || currentPeer->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(currentPeer)->world) {
												pSpawn.CreatePacket(currentPeer);
											}
										}
									}
								}
								else if (cch.find("buttonClicked|textBot") != string::npos) {
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("\nset_default_color|`o"
										"\nadd_label_with_icon|big|`wText Bot Spammer``|left|5016|"
										"\nadd_spacer|small|"
										"\nadd_text_input|textBot|`wText Bot Spammer|" + pInfo(peer)->npc_text + "|50|"
										"\nadd_spacer|small|"
										"\nend_dialog|textSpammer|Cancel|`wOK!|"
									);
									p.CreatePacket(peer);
								}
								else if (cch.find("buttonClicked|deleteBot") != string::npos) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("Success Delete Postion NPC Bot Spammer!!");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(peer);

									gamepacket_t p2;
									p2.Insert("OnRemove");
									p2.Insert("netID|" + to_string(pInfo(peer)->npc_netID) + "\n");

									gamepacket_t p3;
									p3.Insert("OnRemove");
									p3.Insert("netID|" + to_string(pInfo(peer)->npc_netID) + "\n");
									p3.CreatePacket(peer);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED || currentPeer->data == NULL) continue;
										if (pInfo(peer)->npc_world != pInfo(currentPeer)->world) continue;
										p2.CreatePacket(currentPeer);
									}
									pInfo(peer)->x_npc = 0, pInfo(peer)->y_npc = 0;
									pInfo(peer)->npc_world = "";
									pInfo(peer)->npc_netID = 0;
									pInfo(peer)->npc_summon = false;
								}
						}
							else if (cch.find("action|dialog_return\ndialog_name|verify_me") != string::npos) {
								if (pInfo(peer)->is_verified == false) {
									pInfo(peer)->is_verified = true;
									ofstream o("database/verify/" + pInfo(peer)->rid + ".json");
									if (!o.is_open()) cout << "invalid to load verify. make sure verify folder is exists!" << GetLastError() << endl;
									json j;
									j["verified_status"] = pInfo(peer)->is_verified;
									o << j << endl;
									gamepacket_t packet;
									packet.Insert("OnConsoleMessage");
									packet.Insert("`o>> You have `2verified `oyour current device location!");
									packet.CreatePacket(peer);
									packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
									enet_peer_disconnect_later(peer, 0);
								}
							}
							else if (cch.find("action|dialog_return\ndialog_name|remove_bulletin") != string::npos) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									int letter = 0;
									World* world_ = &worlds[p - worlds.begin()];
									for (int i_ = 0; i_ < world_->bulletin.size(); i_++) {
										if (world_->bulletin[i_].x == pInfo(peer)->lastwrenchx and world_->bulletin[i_].y == pInfo(peer)->lastwrenchy) {
											letter++;
											if (pInfo(peer)->lastchoosennr == letter) {
												world_->bulletin.erase(world_->bulletin.begin() + i_);
												{
													gamepacket_t p;
													p.Insert("OnTalkBubble");
													p.Insert(pInfo(peer)->netID);
													p.Insert("`2Bulletin removed.``");
													p.Insert(0), p.Insert(0);
													p.CreatePacket(peer);
												}
											}
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|bulletin_edit\nbuttonClicked|edit") != string::npos) {
								int count = atoi(cch.substr(65, cch.length() - 65).c_str()), letter = 0;
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									for (int i_ = 0; i_ < world_->bulletin.size(); i_++) {
										if (world_->bulletin[i_].x == pInfo(peer)->lastwrenchx and world_->bulletin[i_].y == pInfo(peer)->lastwrenchy) {
											letter++;
											if (count == letter) {
												pInfo(peer)->lastchoosennr = count;
												gamepacket_t p;
												p.Insert("OnDialogRequest");
												p.Insert("set_default_color|`o\nadd_label_with_icon|small|Remove`` \"`w"+ world_->bulletin[i_].text +"\"`` from your board?|left|"+to_string(pInfo(peer)->lastwrenchb) + "|\nend_dialog|remove_bulletin|Cancel|OK|");
												p.CreatePacket(peer);
											}
										}
									}
								}
								break;
							}
						else if (cch.find("action|dialog_return\ndialog_name|storageboxxtreme\nbuttonClicked|change_password") != string::npos) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								if (block_->fg == 8878) {
									if (block_access(peer, world_, block_, false, true)) {
										gamepacket_t p;
										p.Insert("OnDialogRequest");
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSafe Vault``|left|8878|\nadd_smalltext|The ingenious minds at GrowTech bring you the `2Safe Vault`` - a place to store your items safely with its integrated password option!|left|\nadd_smalltext|How the password works:|left|\nadd_smalltext|The Safe Vault requires both a `2password`` and a `2recovery answer`` to be entered to use a password.|left|\nadd_smalltext|Enter your `2password`` and `2recovery answer`` below - keep them safe and `4DO NOT`` share them with anyone you do not trust!|left|\nadd_smalltext|The password and recovery answer can be no longer than 12 characters in length - number and alphabet only please, no special characters are allowed!|left|\nadd_smalltext|If you forget your password, enter your recovery answer to access the Safe Vault - The Safe Vault will `4NOT be password protected now``. You will need to enter a new password.|left|\nadd_smalltext|You can change your password, however you will need to enter the old password before a new one can be used.|left|\nadd_smalltext|`4WARNING``: DO NOT forget your password and recovery answer or you will not be able to access the Safe Vault!|left|\nadd_textbox|`4There is no password currently set on this Safe Vault.``|left|\nadd_textbox|Enter a new password `2(ONLY NUMBER)``|left|\nadd_text_input_password|storage_newpassword|||18|\nadd_textbox|Enter a recovery answer.|left|\nadd_text_input|storage_recoveryanswer|||12|\nadd_button|set_password|Update Password|noflags|0|0|\nend_dialog|storageboxpassword|Exit||\nadd_quick_exit|");
										p.CreatePacket(peer);
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|storageboxpassword") != string::npos) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
								if (block_->fg == 8878) {
									if (world_->owner_name == pInfo(peer)->tankIDName || pInfo(peer)->dev) {
										vector<string> t_ = explode("|", cch);
										if (t_.size() < 4) break;
										string button = explode("\n", t_[3])[0].c_str();
										if (button == "set_password") {
											string text = explode("\n", t_[4])[0].c_str(), text2 = explode("\n", t_[5])[0].c_str();
											replace_str(text, "\n", "");
											replace_str(text2, "\n", "");
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											if (not check_blast(text) || not check_blast(text2)) p.Insert("`4Your input contains special characters. It should only contain alphanumeric characters!``");
											else if (text == "") p.Insert("`4You did not enter a new password!``");
											else if (text2 == "") p.Insert("`4You did not enter a recovery answer!``");
											else if (text.length() > 12 || text2.length() > 12) p.Insert("`4The password is too long! You can only use a maximum of 12 characters!``");
											else {
												p.Insert("`2Your password has been updated!``");
												block_->door_destination = text;
												block_->door_id = text2;
											}
											p.Insert(0), p.Insert(1);
											p.CreatePacket(peer);
										}
										else if (button == "check_password") {
											string password = cch.substr(99, cch.length() - 100).c_str();
											if (password == block_->door_destination) load_storagebox(peer, world_, block_);
											else {
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID), p.Insert("`4The password you e did not match!``"), p.Insert(0), p.Insert(1);
												p.CreatePacket(peer);
											}
										}
										else if (button == "show_recoveryanswer") {
											gamepacket_t p;
											p.Insert("OnDialogRequest");
											p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSafe Vault``|left|8878|\nadd_textbox|Please enter recovery answer.|left|\nadd_text_input|storage_recovery_answer|||12|\nadd_button|check_recovery|Enter Recovery Answer|noflags|0|0|\nend_dialog|storageboxpassword|Exit||\nadd_quick_exit|");
											p.CreatePacket(peer);
										}
										else if (button == "check_recovery") {
											string password = cch.substr(106, cch.length() - 107).c_str();
											if (password == block_->door_id) {
												block_->door_destination = "", block_->door_id = "";
												load_storagebox(peer, world_, block_);
											}
											else {
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID), p.Insert("`4The recovery answer you entered does not match!``"), p.Insert(0), p.Insert(1);
												p.CreatePacket(peer);
											}
										}
									}
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|bulletin_edit\nbuttonClicked|send\n\nsign_text|") != string::npos) {
							vector<string> t_ = explode("|", cch);
							if (t_.size() < 4) break;
								string text = explode("\n", t_[4])[0].c_str();
								replace_str(text, "\n", "");
								if (text.length() <= 2 || text.length() >= 100) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("That's not interesting enough to post.");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(peer);
								}
								else {
									string name_ = pInfo(peer)->world;
									vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									if (p != worlds.end()) {
										{
											World* world_ = &worlds[p - worlds.begin()];
											int letter = 0;
											for (int i_ = 0; i_ < world_->bulletin.size(); i_++) if (world_->bulletin[i_].x == pInfo(peer)->lastwrenchx and world_->bulletin[i_].y == pInfo(peer)->lastwrenchy) letter++;
											if (letter == 21) world_->bulletin.erase(world_->bulletin.begin() + 0);
											WorldBulletin bulletin_{};
											bulletin_.x = pInfo(peer)->lastwrenchx, bulletin_.y = pInfo(peer)->lastwrenchy;
											if (pInfo(peer)->name_color == royal_color || pInfo(peer)->name_color == mod_color || pInfo(peer)->name_color == "`0") bulletin_.name = (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "``";
											else bulletin_.name = "`0" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) + "``";
											bulletin_.text = text;
											world_->bulletin.push_back(bulletin_);
											{
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert(items[pInfo(peer)->lastwrenchb].blockType == BlockTypes::MAILBOX ? "`2You place your letter in the mailbox.``" : "`2Bulletin posted.``");
												p.Insert(0), p.Insert(0);
												p.CreatePacket(peer);
											}
											if (items[pInfo(peer)->lastwrenchb].blockType == BlockTypes::MAILBOX) {
												WorldBlock block_ = world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
												PlayerMoving data_{};
												data_.packetType = 5, data_.punchX = pInfo(peer)->lastwrenchx, data_.punchY = pInfo(peer)->lastwrenchy, data_.characterState = 0x8;
												BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, &block_));
												BYTE* blc = raw + 56;
												form_visual(blc, block_, *world_, peer, false, true);
												for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
													if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
													if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
													send_raw(currentPeer, 4, raw, 112 + alloc_(world_, &block_), ENET_PACKET_FLAG_RELIABLE);
												}
												delete[] raw, blc;
											}
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|storageboxxtreme\nbuttonClicked|do_add\n\nitemcount|") != string::npos) {
								int count = atoi(cch.substr(82, cch.length() - 82).c_str());
								if (pInfo(peer)->lastchoosenitem <= 0 || pInfo(peer)->lastchoosenitem >= items.size()) break;
								if (pInfo(peer)->lastwrenchb != 4516 and items[pInfo(peer)->lastchoosenitem].untradeable == 1 or pInfo(peer)->lastchoosenitem == 1424 or items[pInfo(peer)->lastchoosenitem].blockType == BlockTypes::FISH) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You can't store Untradeable items there!"), p.CreatePacket(peer);
								}
								else if (pInfo(peer)->lastwrenchb == 4516 and items[pInfo(peer)->lastchoosenitem].untradeable == 0 or pInfo(peer)->lastchoosenitem == 1424 || items[pInfo(peer)->lastchoosenitem].blockType == BlockTypes::FISH || pInfo(peer)->lastchoosenitem == 18 || pInfo(peer)->lastchoosenitem == 32 || pInfo(peer)->lastchoosenitem == 6336) {
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You can't store Tradeable items there!"), p.CreatePacket(peer);
								}
								else {
									int got = 0, receive = 0;
									modify_inventory(peer, pInfo(peer)->lastchoosenitem, got);
									if (count <= 0 || count > got) {
										gamepacket_t p;
										p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You don't have that many!"), p.CreatePacket(peer);
									}
									else {
										receive = count * -1;
										string name_ = pInfo(peer)->world;
										vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
										if (p != worlds.end()) {
											World* world_ = &worlds[p - worlds.begin()];
											WorldBlock block_ = world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
											if (items[pInfo(peer)->lastchoosenitem].untradeable == 1 && block_.fg != 4516) break;
											gamepacket_t p1, p2;
											p1.Insert("OnTalkBubble"), p1.Insert(pInfo(peer)->netID), p1.Insert("Stored `w" + to_string(count) + " " + items[pInfo(peer)->lastchoosenitem].name + "`` in " + items[pInfo(peer)->lastwrenchb].name + "."), p1.CreatePacket(peer);
											p2.Insert("OnConsoleMessage"), p2.Insert("Stored `w" + to_string(count) + " " + items[pInfo(peer)->lastchoosenitem].name + "`` in the " + items[pInfo(peer)->lastwrenchb].name + "."), p2.CreatePacket(peer);
											modify_inventory(peer, pInfo(peer)->lastchoosenitem, receive);
											bool dublicated = true;
											for (int i_ = 0; i_ < world_->sbox1.size(); i_++) {
												if (dublicated) {
													if (world_->sbox1[i_].x == pInfo(peer)->lastwrenchx and world_->sbox1[i_].y == pInfo(peer)->lastwrenchy and world_->sbox1[i_].id == pInfo(peer)->lastchoosenitem and world_->sbox1[i_].count + count <= 200) {
														world_->sbox1[i_].count += count;
														dublicated = false;
													}
												}
											}
											if (dublicated) {
												WorldSBOX1 sbox1_{};
												sbox1_.x = pInfo(peer)->lastwrenchx, sbox1_.y = pInfo(peer)->lastwrenchy;
												sbox1_.id = pInfo(peer)->lastchoosenitem, sbox1_.count = count;
												world_->sbox1.push_back(sbox1_);
											}
											PlayerMoving data_{};
											data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16, data_.packetType = 19, data_.plantingTree = 500, data_.punchX = pInfo(peer)->lastchoosenitem, data_.punchY = pInfo(peer)->netID;
											int32_t to_netid = pInfo(peer)->netID;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = 5;
											memcpy(raw + 8, &to_netid, 4);
											send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											delete[] raw;
											edit_tile(peer, pInfo(peer)->lastwrenchx, pInfo(peer)->lastwrenchy, 32);
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|punish_view\nbuttonClicked|oan_") != string::npos) {
								if (pInfo(peer)->owner == 1) {
									if (to_lower(pInfo(peer)->last_wrenched) == creator1) break;
									long long int seconds = atoi(cch.substr(63, cch.length() - 63).c_str());
									string reason = cch.substr(72 + to_string(seconds).length(), cch.length() - 72 + to_string(seconds).length()).c_str();
									replace_str(reason, "\n", "");
									writelog(pInfo(peer)->tankIDName + " " + (seconds == 0 ? "unbanned" : "banned") + " (" + reason + ") - " + pInfo(peer)->last_wrenched);
									string path_ = "database/players/" + pInfo(peer)->last_wrenched + "_.json";
									if (_access_s(path_.c_str(), 0) == 0) {
										json r_;
										ifstream f_(path_, ifstream::binary);
										if (f_.fail()) continue;
										f_ >> r_;
										f_.close();
										{
											json f_ = r_["b_t"].get<int>();
											if (seconds == 729) r_["b_s"] = (6.307e+7 * 1000);
											else if (seconds == 31)r_["b_s"] = (2.678e+6 * 1000);
											else r_["b_s"] = (seconds * 1000);
											r_["b_r"] = reason;
											r_["b_b"] = pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``";
											r_["b_t"] = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
											if (seconds == 0) {
												r_["b_t"] = 0;
												r_["b_s"] = 0;
												r_["b_r"] = "";
												r_["b_b"] = "";
												r_["b_t"] = 0;
												add_modlogs(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, "UNBANNED: " + pInfo(peer)->last_wrenched + "``", "");
											}
											else {
												if (seconds == 729) seconds = 6.307e+7;
												if (seconds == 31) seconds = 2.678e+6;
												add_modlogs(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, "BANNED (" + reason + "): " + pInfo(peer)->last_wrenched + "``", "`#" + ((seconds / 86400 > 0) ? to_string(seconds / 86400) + " days" : (seconds / 3600 > 0) ? to_string(seconds / 3600) + " hours" : (seconds / 60 > 0) ? to_string(seconds / 60) + " minutes" : to_string(seconds) + " seconds"));
											}
										}
										{
											ofstream f_(path_, ifstream::binary);
											f_ << r_;
											f_.close();
										}
									}

								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|punish_view\nbuttonClicked|ban_") != string::npos) {
								if (pInfo(peer)->owner == 1) {
									if (to_lower(pInfo(peer)->last_wrenched) == creator1) break;
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
											long long int seconds = atoi(cch.substr(63, cch.length() - 63).c_str()), sec_time = 0;
											string reason = cch.substr(72 + to_string(seconds).length(), cch.length() - 72 + to_string(seconds).length()).c_str();
											replace_str(reason, "\n", "");
											if (reason == "") {
												gamepacket_t p;
												p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You did not put the reason for a ban!"), p.CreatePacket(peer);
											}
											else {
												sec_time = seconds;
												if (seconds == 729) sec_time = 6.307e+7;
												if (seconds == 31)sec_time = 2.678e+6;
												writelog(pInfo(peer)->tankIDName + " banned (" + reason + ") - " + pInfo(currentPeer)->tankIDName);
												add_ban(currentPeer, sec_time, reason, pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``");
												add_modlogs(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, "BANNED (" + reason + "): " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``", "`#" + ((sec_time / 86400 > 0) ? to_string(sec_time / 86400) + " days" : (sec_time / 3600 > 0) ? to_string(sec_time / 3600) + " hours" : (sec_time / 60 > 0) ? to_string(sec_time / 60) + " minutes" : to_string(sec_time) + " seconds"));
											}
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|punish_view\nbuttonClicked|ipban") != string::npos) {
								if (pInfo(peer)->owner == 1) {
									if (to_lower(pInfo(peer)->last_wrenched) == creator1) break;
									string his_ip = "";
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
											add_ban(currentPeer, 6.307e+7, "No reason", pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``");
											writelog(pInfo(peer)->tankIDName + " ip banned (" + pInfo(currentPeer)->ip + ") - " + pInfo(currentPeer)->tankIDName);
											add_ipban(currentPeer);
										}
									}
									if (not his_ip.empty()) {
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->ip == pInfo(peer)->ip) {
												add_ban(currentPeer, 6.307e+7, "No reason", pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``");
												writelog(pInfo(peer)->tankIDName + " ip banned (" + pInfo(currentPeer)->ip + ") - " + pInfo(currentPeer)->tankIDName);
												add_ipban(currentPeer);
											}
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|punish_view\nbuttonClicked|duc_") != string::npos) {
								if (pInfo(peer)->owner == 1) {
									if (to_lower(pInfo(peer)->last_wrenched) == creator1) break;
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
											int seconds = atoi(cch.substr(63, cch.length() - 63).c_str());
											string reason = cch.substr(72 + to_string(seconds).length(), cch.length() - 72 + to_string(seconds).length()).c_str();
											replace_str(reason, "\n", "");
											if (reason == "") {
												gamepacket_t p;
												p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You did not put the reason for a ban!"), p.CreatePacket(peer);
											}
											else {
												writelog(pInfo(peer)->tankIDName + " duct-taped (" + reason + ") - " + pInfo(currentPeer)->tankIDName);
												add_mute(currentPeer, seconds, reason, pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``");
												add_modlogs(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, "DUCT-TAPED (" + reason + "): " + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "``", "`#" + ((seconds / 86400 > 0) ? to_string(seconds / 86400) + " days" : (seconds / 3600 > 0) ? to_string(seconds / 3600) + " hours" : (seconds / 60 > 0) ? to_string(seconds / 60) + " minutes" : to_string(seconds) + " seconds"));
											}
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|bank_deposit") != string::npos) {
							if (cch.find("buttonClicked|bgls_depo") != string::npos) {
								int bgls = 0, c_ = 0;
								modify_inventory(peer, 7188, c_);
								if (c_ == 0) break;
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wDeposit Blue Gem Locks````|left|7188|\nadd_label|small|Deposit how many? (you have " + to_string(c_) + ")|left|\nadd_text_input|bgl_count|`wAmount:``|" + to_string(c_) + "|3|\nadd_spacer|small|\nadd_button|deposit_bgl|Deposit|noflags|0|0|\nend_dialog|bank_deposit|Nevermind.||");
								p.CreatePacket(peer);
								break;
							}
							else if (cch.find("buttonClicked|deposit_bgl") != string::npos) {
								try {
									int count = atoi(explode("\n", explode("bgl_count|", cch)[1])[0].c_str());
									int got = 0, receive = 0;
									modify_inventory(peer, 7188, got);
									if (count <= 0 || count > got) {
										gamepacket_t p;
										p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You don't have that many!"), p.CreatePacket(peer);
									}
									else if (got == 0) {
										gamepacket_t p;
										p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You don't have that many!"), p.CreatePacket(peer);
									}
									else {
										receive = count * -1;
										string name_ = pInfo(peer)->world;
										vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
										if (p != worlds.end()) {
											gamepacket_t p1, p2;
											p1.Insert("OnTalkBubble"), p1.Insert(pInfo(peer)->netID), p1.Insert("`3You Deposit `w" + to_string(count) + "`e Blue Gem Lock's`w in The bank!"), p1.CreatePacket(peer);
											p2.Insert("OnConsoleMessage"), p2.Insert("`3You Deposit `w" + to_string(count) + "`e Blue Gem Lock's`w in The bank!"), p2.CreatePacket(peer);
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											modify_inventory(peer, 7188, receive);
											pInfo(peer)->bankfixd += count;
										}
									}
								}
								catch (...) {
									break;
								}
							}
							else if (cch.find("buttonClicked|bgls_takes") != string::npos) {
								int bgls = pInfo(peer)->bankfixd;
								if (bgls == 0 || bgls <= 0) break;
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wWithdraw Blue Gem Locks````|left|7188|\nadd_label|small|Withdraw how many? (you have `3" + setGems(bgls) + "``) in the bank!|left|\nadd_text_input|bgl_withdraw|`wAmount:``|0|3|\nadd_spacer|small|\nadd_button|7188w_bgl|`^Withdraw``|noflags|0|0|\nend_dialog|bank_deposit|Nevermind.||");
								p.CreatePacket(peer);
								break;
							}
							else if (cch.find("buttonClicked|7188w_bgl") != string::npos) {
								try {
									int maubrp = atoi(explode("\n", explode("bgl_withdraw|", cch)[1])[0].c_str());
									//int maubrp = 0;
									int bank = 0;
									bank = pInfo(peer)->bankfixd;
									int fler = 0;
									modify_inventory(peer, 7188, fler);
									if (bank < maubrp) {
										gamepacket_t a;
										a.Insert("OnConsoleMessage"), a.Insert("Your BGL in bank doesnt enough");
										a.CreatePacket(peer);
										break;
									}
									if (maubrp > 200) break;
									if (to_string(maubrp).find_first_not_of("1234567890") != string::npos) break;
									int oky = 0;
									modify_inventory(peer, 7188, oky += maubrp);
									pInfo(peer)->bankfixd -= maubrp;
									gamepacket_t a;
									a.Insert("OnConsoleMessage"), a.Insert("You withdraw " + to_string(maubrp) + " From");
									break;
								}
								catch (...) {
									break;
								}
							}
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|betting") != string::npos) {
								if (cch.find("action|dialog_return\ndialog_name|betting\nbgl|1\ndl|0\nwl|0\njumlahbet|") != string::npos) {
									int count = atoi(cch.substr(67, cch.length() - 67).c_str());
									unsigned char p_ = rand() % 27, b_ = rand() % 37;
									int bgl = 0;
									int dl = 0;
									int wl = 0;
									modify_inventory(peer, 7188, bgl);
									modify_inventory(peer, 1796, dl);
									modify_inventory(peer, 242, wl);
									if (count < 1) {
										gamepacket_t p5;
										p5.Insert("OnConsoleMessage"), p5.Insert("`o>> Please enter a numbers only."), p5.CreatePacket(peer);
										break;
									}
									if (count > 1) {
										gamepacket_t p5;
										p5.Insert("OnConsoleMessage"), p5.Insert("`o>> Sorry max bet is 1."), p5.CreatePacket(peer);
										break;
									}
									if (count > bgl) {
										gamepacket_t p5;
										p5.Insert("OnConsoleMessage"), p5.Insert("`oYou don't have enought blue gem lock."), p5.CreatePacket(peer);
										break;
									}
									else {


										if (p_ > b_) {
											int c_ = count;
											if (modify_inventory(peer, 7188, c_) == 0) {
												gamepacket_t p;
												p.Insert("OnDialogRequest");
												p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`o`4" + server_name + " `$Casino System``|left|394|\nadd_spacer|small\nadd_textbox|`5Your bet: `$" + to_string(count) + "`e BGL!|\nadd_spacer|small|\nadd_textbox|`1STATUS: `2WIN!|left|\n\nadd_smalltext|`2" + pInfo(peer)->tankIDName + "`$ spin and got:`4 " + to_string(p_) + "|left|\nadd_smalltext|`4System `$spin and got:`b " + to_string(b_) + "|left|\nadd_spacer|small|\nadd_smalltext|" + (wl + dl != 0 ? "`o(Now your balance is: `9" + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? "`o,`1 " + to_string(dl) + " Diamond Lock" : "") + "" + (bgl != 0 ? "`o, and `e" + to_string(bgl + count) + " Blue Gem Lock" : "") + "`o)``" : "`9(Hmm, smells like you don't care any world locks)``") + "|left|\nadd_spacer|small|\nadd_spacer|small|\nend_dialog|btn_bet|Cancel|`$Play again?``|\n");
												p.CreatePacket(peer);
												break;
											}
											else {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("No inventory space.");
												p.CreatePacket(peer);
												break;
											}
										}
										else {
											if (p_ < b_) {
												int c_ = 0;
												if (modify_inventory(peer, 7188, c_ = -count) == 0) {
													gamepacket_t p;
													p.Insert("OnDialogRequest");
													p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`o`4" + server_name + " `$Casino System``|left|394|\nadd_spacer|small\nadd_textbox|`5Your bet: `$" + to_string(count) + "`e BGL!|\nadd_spacer|small|\nadd_textbox|`1STATUS: `4LOSE!|left|\n\nadd_smalltext|`2" + pInfo(peer)->tankIDName + "`$ spin and got:`4 " + to_string(p_) + "|left|\nadd_smalltext|`4System `$spin and got:`b " + to_string(b_) + "|left|\nadd_spacer|small|\nadd_smalltext|" + (wl + dl != 0 ? "`o(Now your balance is: `9" + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? "`o,`1 " + to_string(dl) + " Diamond Lock" : "") + "" + (bgl != 0 ? "`o, and `e" + to_string(bgl - count) + " Blue Gem Lock" : "") + "`o)``" : "`9(Hmm, smells like you don't care any world locks)``") + "|left|\nadd_spacer|small|\nadd_spacer|small|\nend_dialog|btn_bet|Cancel|`$Play again?``|\n");
													p.CreatePacket(peer);
													break;
												}
												else {
													gamepacket_t p;
													p.Insert("OnConsoleMessage");
													p.Insert("No inventory space.");
													p.CreatePacket(peer);
													break;
												}
											}
										}
									}
								}
								else if (cch.find("action|dialog_return\ndialog_name|betting\nbgl|0\ndl|1\nwl|0\njumlahbet|") != string::npos) {
									int count = atoi(cch.substr(67, cch.length() - 67).c_str());
									unsigned char p_ = rand() % 31, b_ = rand() % 37;
									int bgl = 0;
									int dl = 0;
									int wl = 0;
									modify_inventory(peer, 7188, bgl);
									modify_inventory(peer, 1796, dl);
									modify_inventory(peer, 242, wl);
									if (count < 1) {
										gamepacket_t p5;
										p5.Insert("OnConsoleMessage"), p5.Insert("`o>> Please enter a numbers only."), p5.CreatePacket(peer);
										break;
									}
									if (count > 100) {
										gamepacket_t p5;
										p5.Insert("OnConsoleMessage"), p5.Insert("`o>> Sorry max bet is 100."), p5.CreatePacket(peer);
										break;
									}
									if (count > dl) {
										gamepacket_t p5;
										p5.Insert("OnConsoleMessage"), p5.Insert("`oYou don't have enought diamond lock."), p5.CreatePacket(peer);
										break;
									}
									else {


										if (p_ > b_) {
											int c_ = count;
											if (modify_inventory(peer, 1796, c_) == 0) {
												gamepacket_t p;
												p.Insert("OnDialogRequest");
												p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`o`4S`w-PS `$Casino System``|left|394|\nadd_spacer|small\nadd_textbox|`5Your bet: `$" + to_string(count) + "`1 DL!|\nadd_spacer|small|\nadd_textbox|`1STATUS: `2WIN!|left|\n\nadd_smalltext|`2" + pInfo(peer)->tankIDName + "`$ spin and got:`4 " + to_string(p_) + "|left|\nadd_smalltext|`4System `$spin and got:`b " + to_string(b_) + "|left|\nadd_spacer|small|\nadd_smalltext|" + (wl + dl != 0 ? "`o(Now your balance is: `9" + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? "`o,`1 " + to_string(dl + count) + " Diamond Lock" : "") + "" + (bgl != 0 ? "`o, and `e" + to_string(bgl) + " Blue Gem Lock" : "") + "`o)``" : "`9(Hmm, smells like you don't care any world locks)``") + "|left|\nadd_spacer|small|\nadd_spacer|small|\nend_dialog|btn_bet|Cancel|`$Play again?``|\n");
												p.CreatePacket(peer);
												break;
											}
											else {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("No inventory space.");
												p.CreatePacket(peer);
												break;
											}
										}
										else {
											if (p_ < b_) {
												int c_ = 0;
												if (modify_inventory(peer, 1796, c_ = -count) == 0) {
													gamepacket_t p;
													p.Insert("OnDialogRequest");
													p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`o`4" + server_name + " `$Casino System``|left|394|\nadd_spacer|small\nadd_textbox|`5Your bet: `$" + to_string(count) + "`1 DL!|\nadd_spacer|small|\nadd_textbox|`1STATUS: `4LOSE!|left|\n\nadd_smalltext|`2" + pInfo(peer)->tankIDName + "`$ spin and got:`4 " + to_string(p_) + "|left|\nadd_smalltext|`4System `$spin and got:`b " + to_string(b_) + "|left|\nadd_spacer|small|\nadd_smalltext|" + (wl + dl != 0 ? "`o(Now your balance is: `9" + (wl != 0 ? to_string(wl) + " World Locks" : "") + "" + (dl != 0 ? "`o,`1 " + to_string(dl - count) + " Diamond Lock" : "") + "" + (bgl != 0 ? "`o, and `e" + to_string(bgl) + " Blue Gem Lock" : "") + "`o)``" : "`9(Hmm, smells like you don't care any world locks)``") + "|left|\nadd_spacer|small|\nadd_spacer|small|\nend_dialog|btn_bet|Cancel|`$Play again?``|\n");
													p.CreatePacket(peer);
													break;
												}
												else {
													gamepacket_t p;
													p.Insert("OnConsoleMessage");
													p.Insert("No inventory space.");
													p.CreatePacket(peer);
													break;
												}
											}
										}
									}
								}
								else if (cch.find("action|dialog_return\ndialog_name|betting\nbgl|0\ndl|0\nwl|1\njumlahbet|") != string::npos) {
									int count = atoi(cch.substr(67, cch.length() - 67).c_str());
									unsigned char p_ = rand() % 37, b_ = rand() % 37;
									int bgl = 0;
									int dl = 0;
									int wl = 0;
									modify_inventory(peer, 7188, bgl);
									modify_inventory(peer, 1796, dl);
									modify_inventory(peer, 242, wl);
									if (count < 1) {
										gamepacket_t p5;
										p5.Insert("OnConsoleMessage"), p5.Insert("`o>> Please enter a numbers only."), p5.CreatePacket(peer);
										break;
									}
									if (count > 100) {
										gamepacket_t p5;
										p5.Insert("OnConsoleMessage"), p5.Insert("`o>> Sorry max bet is 200."), p5.CreatePacket(peer);
										break;
									}
									if (count > wl) {
										gamepacket_t p5;
										p5.Insert("OnConsoleMessage"), p5.Insert("`oYou don't have enought world lock."), p5.CreatePacket(peer);
										break;
									}
									else {


										if (p_ > b_) {
											int c_ = count;
											if (modify_inventory(peer, 242, c_) == 0) {
												gamepacket_t p;
												p.Insert("OnDialogRequest");
												p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`o`4" + server_name + " `$Casino System``|left|394|\nadd_spacer|small\nadd_textbox|`5Your bet: `$" + to_string(count) + "`9 WL!|\nadd_spacer|small|\nadd_textbox|`1STATUS: `2WIN!|left|\n\nadd_smalltext|`2" + pInfo(peer)->tankIDName + "`$ spin and got:`4 " + to_string(p_) + "|left|\nadd_smalltext|`4System `$spin and got:`b " + to_string(b_) + "|left|\nadd_spacer|small|\nadd_smalltext|" + (wl + dl != 0 ? "`o(Now your balance is: `9" + (wl != 0 ? to_string(wl + count) + " World Locks" : "") + "" + (dl != 0 ? "`o,`1 " + to_string(dl) + " Diamond Lock" : "") + "" + (bgl != 0 ? "`o, and `e" + to_string(bgl) + " Blue Gem Lock" : "") + "`o)``" : "`9(Hmm, smells like you don't care any world locks)``") + "|left|\nadd_spacer|small|\nadd_spacer|small|\nend_dialog|btn_bet|Cancel|`$Play again?``|\n");
												p.CreatePacket(peer);
												break;
											}
											else {
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("No inventory space.");
												p.CreatePacket(peer);
												break;
											}
										}
										else {
											if (p_ < b_) {
												int c_ = 0;
												if (modify_inventory(peer, 242, c_ = -count) == 0) {
													gamepacket_t p;
													p.Insert("OnDialogRequest");
													p.Insert("set_default_color|`o\n\nadd_label_with_icon|big|`o`4" + server_name + " `$Casino System``|left|394|\nadd_spacer|small\nadd_textbox|`5Your bet: `$" + to_string(count) + "`9 WL!|\nadd_spacer|small|\nadd_textbox|`1STATUS: `4LOSE!|left|\n\nadd_smalltext|`2" + pInfo(peer)->tankIDName + "`$ spin and got:`4 " + to_string(p_) + "|left|\nadd_smalltext|`4System `$spin and got:`b " + to_string(b_) + "|left|\nadd_spacer|small|\nadd_smalltext|" + (wl + dl != 0 ? "`o(Now your balance is: `9" + (wl != 0 ? to_string(wl - count) + " World Locks" : "") + "" + (dl != 0 ? "`o,`1 " + to_string(dl) + " Diamond Lock" : "") + "" + (bgl != 0 ? "`o, and `e" + to_string(bgl) + " Blue Gem Lock" : "") + "`o)``" : "`9(Hmm, smells like you don't care any world locks)``") + "|left|\nadd_spacer|small|\nadd_spacer|small|\nend_dialog|btn_bet|Cancel|`$Play again?``|\n");
													p.CreatePacket(peer);
													break;
												}
												else {
													gamepacket_t p;
													p.Insert("OnConsoleMessage");
													p.Insert("No inventory space.");
													p.CreatePacket(peer);
													break;
												}
											}
										}
									}
								}
								break;
								}
						else if (cch.find("action|dialog_return\ndialog_name|Geoff") != string::npos) {
							if (cch.find("buttonClicked|Bet_Gems") != string::npos) {
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`9Bet with gems!``|left|112|\nadd_text_input|count||1|5|\nadd_button|Ok_Gems|Okay!|noflags|0|0|\nadd_button|back|Cancel|noflags|0|0|\nadd_smalltext|`6You're currently have : " + setGems(pInfo(peer)->gems) + "!``|left|\nend_dialog|Geoff|Nevermind||");
								p.CreatePacket(peer);
							}
							else if (cch.find("buttonClicked|Ok_Gems") != string::npos) {
								try {
									int Total = atoi(explode("\n", explode("count|", cch)[1])[0].c_str());
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
									if (Total > pInfo(peer)->gems) p.Insert("Sorry, you doesn't have enough gems!");
									else if (Total <= 0) p.Insert("Sorry, that's doesn't seems fair!");
									else {
										pInfo(peer)->gems -= Total;
										pInfo(peer)->Bet_What = 0, pInfo(peer)->Gems = Total, pInfo(peer)->Already_Bet = true;
										p.Insert("Succesfully, you has been bet! " + setGems(Total) + " gems!");
										{
											gamepacket_t p;
											p.Insert("OnSetBux");
											p.Insert(pInfo(peer)->gems);
											p.Insert(1);
											p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
											if (pInfo(peer)->supp >= 2) {
												p.Insert((float)33796, (float)1, (float)0);
											}
											p.CreatePacket(peer);
										}
									}
									p.Insert(0), p.Insert(0), p.CreatePacket(peer);
								}
								catch (...) {
									break;
								}
							}
							else if (cch.find("buttonClicked|ok") != string::npos) {
								try {
									int ID = atoi(explode("\n", explode("itemID|", cch)[1])[0].c_str());
									int Total = atoi(explode("\n", explode("count|", cch)[1])[0].c_str());
									int A = -Total, B = Total;
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
									if (modify_inventory(peer, ID, Total) == 0) {
										modify_inventory(peer, ID, A);
										pInfo(peer)->Offer = ID;
										pInfo(peer)->Bet_What = 1, pInfo(peer)->Gems = Total, pInfo(peer)->Already_Bet = true;
										p.Insert("Succesfully, you has been bet! " + setGems(B) + " " + items[ID].name + "!");
									}
									else if (Total <= 0) p.Insert("Sorry, that's doesn't seems fair!");
									else {
										p.Insert("You didn't have enough of them!");
									}
									p.Insert(0), p.Insert(0), p.CreatePacket(peer);
								}
								catch (...) {
									break;
								}
							}
							else if (cch.find("buttonClicked|change_amount") != string::npos) {
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								if (pInfo(peer)->Bet_What == 0) p.Insert("set_default_color|`o\nadd_label_with_icon|big|`9Bet with gems!``|left|112|\nadd_text_input|count||1|5|\nadd_button|Ok_Gems|Okay!|noflags|0|0|\nadd_button|back|Cancel|noflags|0|0|\nadd_smalltext|`6You're currently have : " + setGems(pInfo(peer)->gems) + "!``|left|\nend_dialog|Geoff|Nevermind||");
								else p.Insert("set_default_color|`o\nadd_label_with_icon|big|`9Bet with locks!``|left|" + to_string(pInfo(peer)->Offer == 0 ? 1796 : pInfo(peer)->Offer) + "|\nadd_text_input|count||1|5|\nadd_button|Ok_Locks|Okay!|noflags|0|0|\nadd_button|back|Cancel|noflags|0|0|\nadd_smalltext|`6You're currently Choose : " + items[pInfo(peer)->Offer].name + "!``|left|\nend_dialog|Geoff|Nevermind||");
								p.CreatePacket(peer);
							}
							else if (cch.find("buttonClicked|Bet") != string::npos) {
								int get37 = rand() % 37, get37_2 = rand() % 37;
								string color = "", color2 = "";
								if (get37 == 36 || get37 == 34 || get37 == 32 || get37 == 30 || get37 == 27 || get37 == 25 || get37 == 23 || get37 == 21 || get37 == 19 || get37 == 18 || get37 == 16 || get37 == 12 || get37 == 9 || get37 == 7 || get37 == 5 || get37 == 3 || get37 == 1) color = "`4";
								else if (get37 == 0) color = "`2";
								else color = "`b";
								if (get37_2 == 36 || get37_2 == 34 || get37_2 == 32 || get37_2 == 30 || get37_2 == 27 || get37_2 == 25 || get37_2 == 23 || get37_2 == 21 || get37_2 == 19 || get37_2 == 18 || get37_2 == 16 || get37_2 == 12 || get37_2 == 9 || get37_2 == 7 || get37_2 == 5 || get37_2 == 3 || get37_2 == 1) color2 = "`4";
								else if (get37_2 == 0) color2 = "`2";
								else color2 = "`b";
								string wheel = "`7[``" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "`` spun the wheel and got " + color + to_string(get37) + "``!`7]``";
								string wheel2 = "`7[``Hoster spun the wheel and got " + color2 + to_string(get37_2) + "``!`7]``";
								gamepacket_t p(2000), p1(2000), p2(4000), a(4000), b(6000);
								p1.Insert("OnConsoleMessage"); p1.Insert(wheel);
								p2.Insert("OnConsoleMessage"); p2.Insert(wheel2);
								p.Insert("OnTalkBubble"), a.Insert("OnTalkBubble"), b.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID), a.Insert(pInfo(peer)->netID), b.Insert(pInfo(peer)->netID);
								p.Insert(wheel); a.Insert(wheel2);
								if (get37 > get37_2 and get37_2 != 0 or get37 == 0 and get37_2 != 0) {
									pInfo(peer)->gems += pInfo(peer)->Gems * 2;
									{
										gamepacket_t p(6000);
										p.Insert("OnSetBux");
										p.Insert(pInfo(peer)->gems);
										p.Insert(1);
										p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
										if (pInfo(peer)->supp >= 2) {
											p.Insert((float)33796, (float)1, (float)0);
										}
										p.CreatePacket(peer);
									}
									b.Insert("Congrats you won the bet!");
									packet_(peer, "action|play_sfx\nfile|audio/love_in.wav\ndelayMS|6000");
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == pInfo(peer)->world) {
											PlayerMoving data_{};
											data_.packetType = 17, data_.netID = 46, data_.YSpeed = 46, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
											data_.plantingTree = 6000;
											BYTE* raw = packPlayerMoving(&data_);
											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											delete[] raw;
										}
									}
								}
								else if (get37 == get37_2) {
									b.Insert("You tie with the Hoster! You both knocked!");
									packet_(peer, "action|play_sfx\nfile|audio/loser.wav\ndelayMS|6000");
								}
								else {
									b.Insert("Sorry, you lost the game!");
									packet_(peer, "action|play_sfx\nfile|audio/loser.wav\ndelayMS|6000");
								}
								pInfo(peer)->Bet_What = 0, pInfo(peer)->Gems = 0, pInfo(peer)->Already_Bet = false;
								p2.CreatePacket(peer); p1.CreatePacket(peer); p.CreatePacket(peer), a.CreatePacket(peer), b.CreatePacket(peer);
							}
							else if (cch.find("buttonClicked|back") != string::npos) {
								pInfo(peer)->Offer = 0;
								string Dialog;
								auto SmallLock = 0, BigLock = 0, HugeLock = 0, WorldLock = 0, DiamondLock = 0, BlueGemLock = 0;
								for (auto i = 0; i < pInfo(peer)->inv.size(); i++) {
									if (pInfo(peer)->inv[i].id == 202 && pInfo(peer)->inv[i].count > 0) {
										SmallLock = pInfo(peer)->inv[i].count;
										break;
									}
								}
								for (auto i = 0; i < pInfo(peer)->inv.size(); i++) {
									if (pInfo(peer)->inv[i].id == 204 && pInfo(peer)->inv[i].count > 0) {
										BigLock = pInfo(peer)->inv[i].count;
										break;
									}
								}
								for (auto i = 0; i < pInfo(peer)->inv.size(); i++) {
									if (pInfo(peer)->inv[i].id == 206 && pInfo(peer)->inv[i].count > 0) {
										HugeLock = pInfo(peer)->inv[i].count;
										break;
									}
								}
								for (auto i = 0; i < pInfo(peer)->inv.size(); i++) {
									if (pInfo(peer)->inv[i].id == 242 && pInfo(peer)->inv[i].count > 0) {
										WorldLock = pInfo(peer)->inv[i].count;
										break;
									}
								}
								for (auto i = 0; i < pInfo(peer)->inv.size(); i++) {
									if (pInfo(peer)->inv[i].id == 1796 && pInfo(peer)->inv[i].count > 0) {
										DiamondLock = pInfo(peer)->inv[i].count;
										break;
									}
								}
								for (auto i = 0; i < pInfo(peer)->inv.size(); i++) {
									if (pInfo(peer)->inv[i].id == 7188 && pInfo(peer)->inv[i].count > 0) {
										BlueGemLock = pInfo(peer)->inv[i].count;
										break;
									}
								}
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`9Hoster, the gambler``|left|9436|\nadd_smalltext|Hello there! How're you guys doing right now? Sounds cool would you like bet with me, if you win you get double what you offer and if you lose you walk with `4nothing``!|left|\nadd_smalltext|`6*Note: If the server down/disconnect and you're in betting, all what you bet will lose! Be carefull...|left|\nadd_spacer|small|" + Dialog + "\nadd_spacer|small|\nadd_textbox|Your bet :|left|" + (string(pInfo(peer)->Already_Bet ? (pInfo(peer)->Bet_What == 0 ? "\nadd_button_with_icon|change_amount||frame|" + to_string(pInfo(peer)->Offer) + "||\nadd_custom_margin|x:-40;y:0|\nadd_textbox|Current Bet : " + setGems(pInfo(peer)->Gems) + " gems!|left||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_custom_margin|x:0;y:-80|" : "\nadd_button_with_icon|change_amount||frame|" + to_string(pInfo(peer)->Offer) + "||\nadd_custom_margin|x:-40;y:0|\nadd_textbox|Current Bet : " + to_string(pInfo(peer)->Gems) + " " + items[pInfo(peer)->Offer].name + "|left||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_custom_margin|x:0;y:-80|") : "\nadd_button|Bet_Gems|Bet for amount of gems!|off|0|0|")) + "\nadd_spacer|small|" + (string(pInfo(peer)->Already_Bet ? "\nadd_button|Bet|Lets Play!|noflags|0|0|" : "\nadd_textbox|You didn't bet anything!|left|\nadd_spacer|small|")) + "\nend_dialog|Geoff|Nevermind||");
								p.CreatePacket(peer);
							}
							break;
						}
						else if (cch.find("action|drop") != string::npos) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									vector<string> t_ = explode("|", cch);
									if (t_.size() < 4) break;
									int id_ = atoi(explode("\n", t_[3])[0].c_str()), c_ = 0;
									if (id_ <= 0 or id_ >= items.size()) break;

									if (find(world_->active_jammers.begin(), world_->active_jammers.end(), 4758) != world_->active_jammers.end()) {
										if (world_->owner_name != (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->tankIDName) and not pInfo(peer)->dev and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end()) {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("The Mini-Mod says no dropping items in this world!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
											break;
										}
									}
									if (items[id_].untradeable or id_ == 1424) {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("You can't drop that.");
										p.CreatePacket(peer);
										break;
									}
									if (items[id_].untradeable or id_ == 6260) {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("You can't drop that.");
										p.CreatePacket(peer);
										break;
									}
									if (items[id_].untradeable or id_ == 5816) {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("You can't drop that.");
										p.CreatePacket(peer);
										break;
									}
									string name_ = pInfo(peer)->world;
									vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									if (p != worlds.end()) {
										World* world_ = &worlds[p - worlds.begin()];
										int a_ = rand() % 12;
										int x = (pInfo(peer)->state == 16 ? pInfo(peer)->x - (a_ + 20) : (pInfo(peer)->x + 20) + a_);
										int y = pInfo(peer)->y + rand() % 16;
										//BlockTypes type_ = FOREGROUND;
										int where_ = (pInfo(peer)->state == 16 ? x / 32 : round((double)x / 32)) + (y / 32 * 100);
										if (where_ < 0 || x < 0 || y < 0 || where_ > 5399) continue;
										WorldBlock* block_ = &world_->blocks[where_];
										if (items[block_->fg].collisionType == 1 || block_->fg == 6 || items[block_->fg].entrance || items[block_->fg].toggleable and is_false_state(world_->blocks[(pInfo(peer)->state == 16 ? x / 32 : round((double)x / 32)) + (y / 32 * 100)], 0x00400000)) {
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert(items[block_->fg].blockType == BlockTypes::MAIN_DOOR ? "You can't drop items on the white door." : "You can't drop that here, face somewhere with open space.");
											p.CreatePacket(peer);
											break;
										}
										/*if (static_(type_, items[world_->blocks[((pInfo(peer)->state == 16 ? pInfo(peer)->x - 18 : pInfo(peer)->x + 22) / 32] + ((y / 32) * 100)).fg)) or static_(type_, items[world_->blocks[((pInfo(peer)->state == 16 ? pInfo(peer)->x - 24 : pInfo(peer)->x + 42) / 32] + ((y / 32) * 100)).fg))) {
											if (items[block_->fg].collisionType == 1) {
												gamepacket_t p;
												p.Insert("OnTextOverlay");
												p.Insert(type_ == MAIN_DOOR ? "You can't drop items on the white door." : "You can't drop that here, face somewhere with open space.");
												p.CreatePacket(peer);
												break;
											}
										}*/
										if (pInfo(peer)->Cheat_FastDrop) {
											modify_inventory(peer, id_, c_);
											WorldDrop drop_block_{};
											drop_block_.x = (pInfo(peer)->state == 16 ? pInfo(peer)->x - ((rand() % 12) + 18) : pInfo(peer)->x + ((rand() % 12) + 22)), drop_block_.y = pInfo(peer)->y + rand() % 16, drop_block_.id = id_, drop_block_.count = c_, drop_block_.uid = uint16_t(world_->drop.size()) + 1;
											dropas_(world_, drop_block_);
											int remove = -c_;
											modify_inventory(peer, id_, remove);
											break;
										}
										if (pInfo(peer)->Cheat_FastDrop) {
											modify_inventory(peer, id_, c_);
											WorldDrop drop_block_{};
											drop_block_.x = (pInfo(peer)->state == 16 ? pInfo(peer)->x - ((rand() % 12) + 18) : pInfo(peer)->x + ((rand() % 12) + 22)), drop_block_.y = pInfo(peer)->y + rand() % 16, drop_block_.id = id_, drop_block_.count = c_, drop_block_.uid = uint16_t(world_->drop.size()) + 1;
											dropas_(world_, drop_block_);
											int remove = -c_;
											modify_inventory(peer, id_, remove);
											break;
										}
										int count_ = 0;
										bool dublicated = false;
										for (int i_ = 0; i_ < world_->drop.size(); i_++) {
											if (abs(world_->drop[i_].y - y) <= 16 and abs(world_->drop[i_].x - x) <= 16) {
												count_ += 1;
											}
											if (world_->drop[i_].id == id_) if (world_->drop[i_].count < 200) dublicated = true;
										}
										if (!dublicated) {
											if (count_ > 20) {
												gamepacket_t p;
												p.Insert("OnTextOverlay");
												p.Insert("You can't drop that here, find an emptier spot!");
												p.CreatePacket(peer);
												break;
											}
										}
									}
									modify_inventory(peer, id_, c_);
									{
										gamepacket_t p;
										p.Insert("OnDialogRequest");
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`w" + items[id_].ori_name + "``|left|" + to_string(id_) + "|\nadd_textbox|How many to drop?|left|\nadd_text_input|count||" + to_string(c_) + "|5|\nembed_data|itemID|" + to_string(id_) + "" + (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and (!guild_access(peer, world_->guild_id) and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end()) ? "\nadd_textbox|If you are trying to trade an item with another player, use your wrench on them instead to use our Trade System! `4Dropping items is not safe!``|left|" : "") + "\nend_dialog|drop_item|Cancel|OK|");
										p.CreatePacket(peer);
									}
								}
								break;
								}
							else if (cch.find("action|setRoleIcon") != string::npos || cch.find("action|setRoleSkin") != string::npos) {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 3) break;
								string id_ = explode("\n", t_[2])[0];
								if (not isdigit(id_[0])) break;
								uint32_t role_t = atoi(id_.c_str());
								if (cch.find("action|setRoleIcon") != string::npos) {
									if (role_t == 6) pInfo(peer)->roleIcon = role_t;
									else if (role_t == 0 and pInfo(peer)->t_lvl >= 50) pInfo(peer)->roleIcon = role_t;
									else if (role_t == 1 and pInfo(peer)->bb_lvl >= 50) pInfo(peer)->roleIcon = role_t;
									else if (role_t == 2 and pInfo(peer)->titleDoctor) pInfo(peer)->roleIcon = role_t;
									else if (role_t == 3 and pInfo(peer)->titleFisher) pInfo(peer)->roleIcon = role_t;
									else if (role_t == 4 and pInfo(peer)->titleChef) pInfo(peer)->roleIcon = role_t;
									else if (role_t == 5 and pInfo(peer)->titleStartopia) pInfo(peer)->roleIcon = role_t;
								}
								else {
									if (role_t == 6) pInfo(peer)->roleSkin = role_t;
									else if (role_t == 0 and pInfo(peer)->t_lvl >= 50) pInfo(peer)->roleSkin = role_t;
									else if (role_t == 1 and pInfo(peer)->bb_lvl >= 50) pInfo(peer)->roleSkin = role_t;
									else if (role_t == 2 and pInfo(peer)->unlockRoleSkin) pInfo(peer)->roleSkin = role_t;
									else if (role_t == 3 and pInfo(peer)->unlockRoleSkin) pInfo(peer)->roleSkin = role_t;
									else if (role_t == 4 and pInfo(peer)->unlockRoleSkin) pInfo(peer)->roleSkin = role_t;
									else if (role_t == 5 and pInfo(peer)->unlockRoleSkin) pInfo(peer)->roleSkin = role_t;
								}
								gamepacket_t p(0, pInfo(peer)->netID);
								p.Insert("OnSetRoleSkinsAndIcons"), p.Insert(pInfo(peer)->roleSkin), p.Insert(pInfo(peer)->roleIcon), p.Insert(0);
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != pInfo(peer)->world) continue;
									p.CreatePacket(currentPeer);
								}
								break;
						}

							else if (cch.find("action|setSkin") != string::npos) {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 3) break;
								string id_ = explode("\n", t_[2])[0];
								if (not isdigit(id_[0])) break;
								char* endptr = NULL;
								unsigned int skin_ = strtoll(id_.c_str(), &endptr, 10);
								if (skin_ == 3317842336 and pInfo(peer)->supp == 2 or skin_ == 3578898848 and pInfo(peer)->supp == 2 or skin_ == 3531226367 and pInfo(peer)->supp == 2 or skin_ == 4023103999 and pInfo(peer)->supp == 2 or skin_ == 1345519520 and pInfo(peer)->supp == 2 or skin_ == 194314239 and pInfo(peer)->supp == 2) pInfo(peer)->skin = skin_;
								else if (skin_ == 3578898848 and pInfo(peer)->gp or skin_ == 3317842336 and pInfo(peer)->gp) pInfo(peer)->skin = skin_;
								else if (skin_ != 1348237567 and skin_ != 1685231359 and skin_ != 2022356223 and skin_ != 2190853119 and skin_ != 2527912447 and skin_ != 2864971775 and skin_ != 3033464831 and skin_ != 3370516479) {
									if (pInfo(peer)->supp >= 1) {
										if (skin_ != 2749215231 and skin_ != 3317842431 and skin_ != 726390783 and skin_ != 713703935 and skin_ != 3578898943 and skin_ != 4042322175) break;
										else pInfo(peer)->skin = skin_;
									}
									else break;
								}
								else pInfo(peer)->skin = skin_;
								update_clothes(peer);
								break;
							}
							else if (cch.find("action|trash") != string::npos) {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								int id_ = atoi(explode("\n", t_[3])[0].c_str()), c_ = 0;
								if (id_ <= 0 or id_ >= items.size()) break;
								gamepacket_t p;
								if (id_ == 18 || id_ == 32 || id_ == 6336 || id_ == 8430) {
									packet_(peer, "action|play_sfx\nfile|audio/cant_place_tile.wav\ndelayMS|0");
									p.Insert("OnTextOverlay"), p.Insert("You'd be sorry if you lost that!"), p.CreatePacket(peer);
									break;
								}
								modify_inventory(peer, id_, c_); // gauna itemo kieki
							if (pInfo(peer)->Cheat_FastTrash) {
								int adaBrp = c_, hapusBrp = 0;
								hapusBrp = 0 - c_;
								if (items[id_].untradeable) {
									int has_ = 0;
									modify_inventory(peer, id_, has_);
									if (has_ < c_) break;
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Recycle`` " + to_string(adaBrp) + " `w" + items[id_].name + "``|left|" + to_string(id_) + "|\nembed_data|itemID|" + to_string(id_) + "\nembed_data|count|" + to_string(adaBrp) + "\nadd_textbox|You are recycling an `9UNTRADEABLE`` item. Are you absolutely sure you want to do this? There is no way to get the item back if you select yes.|left|\nend_dialog|trash_item2|NO!|Yes, I am sure|");
									p.CreatePacket(peer);
									break;
								}
								if (modify_inventory(peer, id_, hapusBrp) == 0) {
									packet_(peer, "action|play_sfx\nfile|audio/trash.wav\ndelayMS|0");
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									if (pInfo(peer)->supp != 0) {
										int item = id_, maxgems = 0, receivegems = 0;
										int count = adaBrp;
										if (id_ % 2 != 0) item -= 1;
										maxgems = items[item].max_gems2;
										if (items[item].max_gems2 != 0) if (maxgems != 0) for (int i = 0; i < count; i++) receivegems += rand() % maxgems;
										if (items[item].max_gems3 != 0) receivegems = count * items[item].max_gems3;
										if (receivegems != 0) {
											pInfo(peer)->gems += receivegems;
											gamepacket_t p;
											p.Insert("OnSetBux");
											p.Insert(pInfo(peer)->gems);
											p.Insert(0);
											p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
											if (pInfo(peer)->supp >= 2) {
												p.Insert((float)33796, (float)1, (float)0);
											}
											p.CreatePacket(peer);
										}
										p.Insert((items[id_].blockType == BlockTypes::FISH ? (to_string(abs(c_))) + "lb." : to_string(adaBrp)) + " `w" + items[id_].ori_name + "`` recycled, `0" + setGems(receivegems) + "`` gems earned.");
									}
									else p.Insert((items[id_].blockType == BlockTypes::FISH ? (to_string(abs(c_))) + "lb." : to_string(adaBrp)) + " `w" + items[id_].ori_name + "`` trashed.");
									p.CreatePacket(peer);
									break;
								}
								break;
							}
							else {
								p.Insert("OnDialogRequest");
								if (pInfo(peer)->supp == 0) p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Trash`` `w" + items[id_].ori_name + "``|left|" + to_string(id_) + "|\nadd_textbox|How many to `4destroy``? (you have " + to_string(c_) + ")|left|\nadd_text_input|count||0|5|\nembed_data|itemID|" + to_string(id_) + "\nend_dialog|trash_item|Cancel|OK|");
								else {
									int item = id_, maxgems = 0, maximum_gems = 0;
									if (id_ % 2 != 0) item -= 1;
									maxgems = items[item].max_gems2;
									if (items[item].max_gems3 != 0) maximum_gems = items[item].max_gems3;
									string recycle_text = "0" + (maxgems == 0 ? "" : "-" + to_string(maxgems)) + "";
									if (maximum_gems != 0) recycle_text = to_string(maximum_gems);
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Recycle`` `w" + items[id_].ori_name + "``|left|" + to_string(id_) + "|\nadd_textbox|You will get " + recycle_text + " gems per item.|\nadd_textbox|How many to `4destroy``? (you have " + to_string(c_) + ")|left|\nadd_text_input|count||0|5|\nembed_data|itemID|" + to_string(id_) + "\nend_dialog|trash_item|Cancel|OK|");
								}
								p.CreatePacket(peer);
								break;
							}
							break;
						}
							else if (cch.find("action|info") != string::npos) {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								int id_ = atoi(explode("\n", t_[3])[0].c_str());
								if (id_ % 2 != 0) p.Insert("set_default_color|`o\nadd_label_with_ele_icon|big|`wAbout " + items[id_].ori_name + "``|left|" + to_string(id_) + "|" + to_string(items[id_ - 1].chi) + "|\nadd_spacer|small|\nadd_textbox|Plant this seed to grow a `0" + items[id_ - 1].ori_name + " Tree.``|left|\nadd_spacer|small|\nadd_textbox|Rarity: `0" + to_string(items[id_].rarity) + "``|left|\nadd_spacer|small|\nend_dialog|continue||OK|\n");
								else {
									string extra_ = "\nadd_textbox|";
									if (id_ == 18) {
										extra_ += "You've punched `w" + to_string(pInfo(peer)->punch_count) + "`` times.";
									} if (items[id_].blockType == BlockTypes::LOCK) {
										extra_ += "A lock makes it so only you (and designated friends) can edit an area.";
									} if (items[id_].r_1 == 0 or items[id_].r_2 == 0) {
										extra_ += "<CR>This item can't be spliced.";
									}
									else {
										extra_ += "Rarity: `w" + to_string(items[id_].rarity) + "``<CR><CR>To grow, plant a `w" + items[id_ + 1].name + "``.   (Or splice a `w" + items[items[id_].r_1].name + "`` with a `w" + items[items[id_].r_2].name + "``)<CR>";
									} if (items[id_].properties & Property_Dropless or items[id_].rarity == 999) {
										extra_ += "<CR>`1This item never drops any seeds.``";
									} if (items[id_].properties & Property_Untradable) {
										extra_ += "<CR>`1This item cannot be dropped or traded.``";
									} if (items[id_].properties & Property_AutoPickup) {
										extra_ += "<CR>`1This item can't be destroyed - smashing it will return it to your backpack if you have room!``";
									} if (items[id_].properties & Property_Wrenchable) {
										extra_ += "<CR>`1This item has special properties you can adjust with the Wrench.``";
									} if (items[id_].properties & Property_MultiFacing) {
										extra_ += "<CR>`1This item can be placed in two directions, depending on the direction you're facing.``";
									} if (items[id_].properties & Property_NoSelf) {
										extra_ += "<CR>`1This item has no use... by itself.``";
									}
									extra_ += "|left|";
									if (extra_ == "\nadd_textbox||left|") extra_ = "";
									else extra_ = replace_str(extra_, "add_textbox|<CR>", "add_textbox|");

									string extra_ore = "";
									if (id_ == 9386 || id_ == 5136 || id_ == 7960) extra_ore = rare_text;
									p.Insert("set_default_color|`o\nadd_label_with_ele_icon|big|`wAbout " + items[id_].name + "``|left|" + to_string(id_) + "|" + to_string(items[id_].chi) + "|\nadd_spacer|small|\nadd_textbox|" + items[id_].description + "|left|"+(extra_ore != "" ? "\nadd_spacer|small|\nadd_textbox|This item also drops:|left|" + extra_ore : "") + "" + (id_ == 8552 ? "\nadd_spacer|small|\nadd_textbox|Angelic Healings: " + to_string(pInfo(peer)->surgery_done) + "|left|" : "") + "\nadd_spacer|small|" + extra_ + "\nadd_spacer|small|\nembed_data|itemID|" + to_string(id_) + "\nend_dialog|continue||OK|\n");
								}
								p.CreatePacket(peer);
								break;
							}
						if (cch.find("action|dialog_return\ndialog_name|find_item_dialog\nbuttonClicked|back") != string::npos) find_item_dialog(peer, "dialog");
						if (cch.find("action|dialog_return\ndialog_name|find_item_dialog\nbuttonClicked|check") != string::npos) find_item_dialog(peer, "feeling_lucky");
						if (cch.find("action|dialog_return\ndialog_name|find_item_dialog\nbuttonClicked|combining") != string::npos) find_item_dialog(peer, "combining");

						else if (cch.find("action|dialog_return\ndialog_name|find_item_dialog\nbuttonClicked|search") != string::npos) {
							string get_name = explode("|", cch.substr(cch.find("find_item_name"))).back();
							get_name.pop_back();
							string lower_name = get_name;
							to_lower(lower_name);
							string dialog = "set_default_color|`o";
							dialog += "\nadd_label_with_icon|big|`sBook of Knowledge|left|6336|";
							int get_info = 0;
							string cancel_dialog;
							if (lower_name.length() < 3) break;
							for (ItemDB const& item : items) {
								if (item.id % 2 != 0) continue;
								if (to_lower(item.name).find(lower_name) != string::npos and (item.name).find("Guild Potion") and (item.name).find("Guild") and (item.name).find("World Key") and (item.name).find("Guild Banner") and (item.name).find("Guild Lock") and (item.name).find("Friends Entrance") and (item.name).find("Guild Entrance") and (item.name).find("Guild Flag") and (item.name).find("Safe Vault") and (item.name).find("Bountiful Blast") and (item.name).find("Bountiful White Doll's")) {
									get_info++;
									cancel_dialog += "\nadd_label_with_icon|small|" + item.name + "|left|" + std::to_string(item.id) + "|\nadd_smalltext|`oRarity: `5" + std::to_string(item.rarity) + " `oItem ID: `^" + std::to_string(item.id) + "|\n"; //\nadd_smalltext|`oRarity: `^" + std::to_string(item.rarity) + " `oitem ID: `5" + std::to_string(item.id) + "|
								}
							}
							dialog += "\nadd_smalltext|`sBook of Knowledge `oResults Founded: `0" + (get_info == 0 ? "None" : std::to_string(get_info)) + "|";
							dialog += "\nadd_smalltext|`oRandering Speed (`2000.000.0001 `wmilisecond`o)|";
							dialog += "\nadd_smalltext|`oThe `pBook of Love & Knowledge `oBook allows you to check obtainability info for any item! To get started, type in a query.";
							dialog += "\nadd_text_input|find_item_name|`oSearch|" + get_name + "|30|";
							dialog += "\nadd_smalltext|`oPress `5Search `oto start. You can also press `^I'm Feeling Lucky `oto look for a random item... `oAnd you might wanna see the combining recipe by click on `1Combning!``|";
							dialog += "\nadd_button|search|`5Search|noflags|0|0|";
							dialog += "\nadd_button|check|`^I'm Feeling Lucky|noflags|0|0|\n";
							dialog += "\nadd_button|combining|`1Combining|noflags|0|0|\n";
							dialog += cancel_dialog;
							if (get_info == 0)
								dialog += "\nadd_textbox|`^Items does not found on database list!|";
							dialog += "\nadd_button|back|`wBack|noflags|0|0|";
							dialog += "\nend_dialog|find_item_dialog|Close!||";
							dialog += "\nadd_quick_exit|";
							dialog += "\nadd_spacer|big|";
							gamepacket_t packet;
							packet.Insert("OnDialogRequest");
							packet.Insert(dialog);
							packet.CreatePacket(peer);
							break;
						}
						
							else if (cch.find("action|wrench") != string::npos) {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								int netID = atoi(explode("\n", t_[3])[0].c_str());
								if (pInfo(peer)->netID == netID) {
									send_wrench_self(peer);
								}
								else if (netID == pInfo(peer)->npc_netID) {
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("\nset_default_color|`o"
										"\nadd_label_with_icon|big|`2Bot Spammer Setting``|left|12158|"
										"\nadd_spacer|small|"
										"\nadd_image_button|bannerss321|interface/large/az_8x1_adv1.rttex|bannerlayout|OPENSURVEY||"
										"\nadd_spacer|small|"
										"\nadd_button|deleteBot|Delete Position Bot|noflags|0|0|"
										"\nadd_button|textBot|Set Spammer Text|noflags|0|0|"
										"\nadd_spacer|small|"
										"\nend_dialog|botSpammer|Cancel|`wContinue|");
									p.CreatePacket(peer);
								}
								else {
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										else if (pInfo(currentPeer)->npc_netID == netID and pInfo(currentPeer)->npc_world == pInfo(peer)->world) {
											gamepacket_t p;
											p.Insert("OnDialogRequest");
											p.Insert("\nset_default_color|`o"
												"\nadd_label_with_icon|big|`2Bot Spammer Setting``|left|12158|"
												"\nadd_spacer|small|"
												"\nadd_image_button|bannerss321|interface/large/az_8x1_adv1.rttex|bannerlayout|OPENSURVEY||"
												"\nadd_spacer|small|"
												"\nadd_button|deleteBot|Delete Position Bot|noflags|0|0|"
												"\nadd_button|textBot|Set Spammer Text|noflags|0|0|"
												"\nadd_spacer|small|"
												"\nend_dialog|botSpammer|Cancel|`wContinue|");
											p.CreatePacket(peer);
										}
										else if (pInfo(currentPeer)->netID == netID and pInfo(currentPeer)->world == pInfo(peer)->world) {
											bool already_friends = false, trade_blocked = false, muted = false;
											for (int c_ = 0; c_ < pInfo(peer)->friends.size(); c_++) {
												if (pInfo(peer)->friends[c_].name == pInfo(currentPeer)->tankIDName) {
													already_friends = true;
													if (pInfo(peer)->friends[c_].block_trade)
														trade_blocked = true;
													if (pInfo(peer)->friends[c_].mute)
														muted = true;
													break;
												}
											}
											pInfo(peer)->last_wrenched = pInfo(currentPeer)->tankIDName;
											string name_ = pInfo(peer)->world;
											if (pInfo(peer)->Cheat_FastPull) {
												SendCmd(peer, "/pull " + pInfo(peer)->last_wrenched, true);
												break;
											}
											if (pInfo(peer)->cheat_kick == 1) {
												SendCmd(peer, "/kick " + pInfo(peer)->last_wrenched, true);
												break;
											}
											if (pInfo(peer)->cheat_ban == 1) {
												SendCmd(peer, "/ban " + pInfo(peer)->last_wrenched, true);
												break;
											}
											vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
											if (p != worlds.end()) {
												World* world_ = &worlds[p - worlds.begin()];
												string msg2 = "";
												for (int i = 0; i < to_string(pInfo(currentPeer)->level).length(); i++) msg2 += "?";
												string inv_guild = "";
												string extra = "";
												if (pInfo(currentPeer)->guild_id != 0) {
													uint32_t guild_id = pInfo(currentPeer)->guild_id;
													vector<Guild>::iterator find_guild = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
													if (find_guild != guilds.end()) {
														Guild* guild_information = &guilds[find_guild - guilds.begin()];
														for (GuildMember member_search : guild_information->guild_members) {
															if (member_search.member_name == pInfo(currentPeer)->tankIDName) {
																if (guild_information->guild_mascot[1] == 0 and guild_information->guild_mascot[0] == 0) {
																	extra += "\nadd_label_with_icon|small|`9Guild: `2" + guild_information->guild_name + "``|left|5814|\nadd_textbox|`9Rank: `2" + (member_search.role_id == 0 ? "Member" : (member_search.role_id == 1 ? "Elder" : (member_search.role_id == 2 ? "Co-Leader" : "Leader"))) + "``|left|\nadd_spacer|small|";
																}
																else {
																	extra += "\nadd_dual_layer_icon_label|small|`9Guild: `2" + guild_information->guild_name + "``|left|" + to_string(guild_information->guild_mascot[1]) + "|" + to_string(guild_information->guild_mascot[0]) + "|1.0|1|\nadd_smalltext|`9Rank: `2" + (member_search.role_id == 0 ? "Member" : (member_search.role_id == 1 ? "Elder" : (member_search.role_id == 2 ? "Co-Leader" : "Leader"))) + "``|left|\nadd_spacer|small|";
																}
																break;
															}
														}
													}
												} if (pInfo(peer)->guild_id != 0 and pInfo(currentPeer)->guild_id == 0) {
													uint32_t guild_id = pInfo(peer)->guild_id;
													vector<Guild>::iterator find_guild = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
													if (find_guild != guilds.end()) {
														Guild* guild_information = &guilds[find_guild - guilds.begin()];
														for (GuildMember member_search : guild_information->guild_members) {
															if (member_search.member_name == pInfo(peer)->tankIDName) {
																if (member_search.role_id >= 1) {
																	inv_guild = "\nadd_button|invitetoguild|`2Invite to Guild``|noflags|0|0|";
																}
																break;
															}
														}
													}
												}
												string surgery = "\nadd_spacer|small|\nadd_button|start_surg|`$Perform Surgery``|noflags|0|0|\nadd_smalltext|Surgeon Skill: "+to_string(pInfo(peer)->surgery_skill) + "|left|";
												for (int i_ = 0; i_ < pInfo(currentPeer)->playmods.size(); i_++) if (pInfo(currentPeer)->playmods[i_].id == 89) surgery = "\nadd_spacer|small|\nadd_textbox|Recovering from surgery...|left|";
												if (pInfo(currentPeer)->hospital_bed == false) surgery = "";
												extra += "\nadd_textbox|`2Player information``|left|";//This account was created `w" + to_string(days_ - pInfo(peer)->account_created+ "`` days ago.``)
												extra += "\nadd_label_with_icon|small|Player `cPremium World Lock: `w" + setGems(pInfo(currentPeer)->gtwl) + "|left|244|";
												extra += "\nadd_label_with_icon|small|Player `eBlue Gem Lock `oon bank: `w" + setGems(pInfo(currentPeer)->bankfixd) + "|left|7188|";
												extra += "\nadd_label_with_icon|small|Player `eBackpack: `w" + setGems(pInfo(currentPeer)->inv.size() - 1) + "|left|9412|";
												extra += "\nadd_label_with_icon|small|Player `9Gems`o: `w" + setGems(pInfo(currentPeer)->gems) + "|left|9436|";
												//extra += "\nadd_label_with_icon|small|Player `wAge`o: `w" + setGems(pInfo(currentPeer)->account_created) + " `wdays ago.``|left|12026|";
												extra += "\nadd_spacer|small|";
												gamepacket_t p;
												p.Insert("OnDialogRequest");
												p.Insert("embed_data|netID|" + to_string(pInfo(peer)->netID) + "\nset_default_color|`o\nadd_label_with_icon|big|" + (pInfo(currentPeer)->mod && pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->name_color : "`0") + "" + (pInfo(currentPeer)->d_name.empty() ? pInfo(currentPeer)->tankIDName : pInfo(currentPeer)->d_name) + "`` `0(```2" + (pInfo(currentPeer)->dev && pInfo(currentPeer)->d_name.empty() ? msg2 : to_string(pInfo(currentPeer)->level)) + "```0)``|left|18|" + surgery + "\nembed_data|netID|" + to_string(netID) + "\nadd_spacer|small|" + extra + (trade_blocked ? "\nadd_button||`4Trade Blocked``|disabled|||" : "\nadd_button|trade|`wTrade``|noflags|0|0|") + "\nadd_textbox|(No Battle Leash equipped)|left|\nadd_textbox|Your opponent needs a valid license to battle!|left|" + (world_->owner_name == pInfo(peer)->tankIDName or (guild_access(peer, world_->guild_id) or find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) != world_->admins.end()) or pInfo(peer)->dev + pInfo(peer)->mod > 0 ? "\nadd_button|kick|`4Kick``|noflags|0|0|\nadd_button|pull|`5Pull``|noflags|0|0|\nadd_button|worldban|`4World Ban``|noflags|0|0|" : "") + (pInfo(peer)->mod == 1 || pInfo(peer)->dev == 1 ? "\nadd_button|punish_view|`5Punish/View``|noflags|0|0|" : "") + inv_guild + (!already_friends ? "\nadd_button|friend_add|`wAdd as friend``|noflags|0|0|" : "") + (muted ? "\nadd_button|unmute_player|`wUnmute``|noflags|0|0|" : (already_friends ? "\nadd_button|mute_player|`wMute``|noflags|0|0|" : "")) + ""/*"\nadd_button|ignore_player|`wIgnore Player``|noflags|0|0|\nadd_button|report_player|`wReport Player``|noflags|0|0|"*/"\nadd_spacer|small|\nend_dialog|popup||Continue|\nadd_quick_exit|");
												p.CreatePacket(peer);
											}
											break;
										}
									}
								}
								break;
							}
							if (cch.find("action|dialog_return\ndialog_name|item_dialog") != string::npos) {
								string item_text = "You must `9choose item `2(item_1 (Pickaxe), item_2 (Mythical Rayman), item_3 (Legendary Rayman) Dan yang lainnya di ItemDB.json";
								string itemid_text = "You must `9add itemid `2(98 (Pickaxe), etc";
								string far_text = "You Must `9add count far `2(1,2,3, further)";
								string gems_text = "You Must `9add multiple gems `2(1,2,3, further)";
								string hit_text = "You Must `9add hit count `2(1,2,3, further)";
								string drop_prize_text = "You Must `9add The price `2(242 (WL), 1796 (DL), etc)";
								string drop_count_text = "You Must `9add The count of dropping `2(1,2,3, further)";

								// file item type itemDB.JSON
								if (cch.find("buttonClicked|change_item_type") != string::npos) {
									DialogBuilder item;
									item.add_label_icon(true, 32, "`cItem type setting``")
										.add_smalltext("NOTE: IT WILL CHANGE IN FILE itemDB ")
										.add_smalltext("Change to itemid `999999` 0if you want to default it, `4dont to 0 because it will bug")
										.add_spacer(false);
									for (int i = 1; i < 11; i++) {
										std::ifstream configFile("./config/itemDB.json");
										if (!configFile.is_open()) {
											std::cout << "Failed to open config.json" << std::endl;

										}
										nlohmann::json config;
										configFile >> config;
										configFile.close();
										string text = "item_" + to_string(i);
										int itemid = config[text]["itemid"].get<int>();
										// + " (" + items.at(itemid).name + ")"
										item.add_smalltext(string(text) + ": " + to_string(itemid));
									}
									item.add_spacer(false)
										.add_smalltext(std::string(item_text))
										.add_text_input(7, "choose_item_type", "`9Item type:", "item_1")
										.add_spacer(false)
										.add_smalltext(std::string(itemid_text))
										.add_text_input(6, "choose_item_id", "`9ItemID:", "")
										.add_spacer(false)
										.add_button("go_change_type", "`2Change!")
										.end_dialog("item_dialog", "Cancel", "");
									enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(item.to_string()).pack());
								}
								if (cch.find("buttonClicked|go_change_type") != string::npos) {
									string choose_item_type = explode("\n", explode("choose_item_type|", cch)[1])[0];
									int choose_item_id = atoi(explode("\n", explode("choose_item_id|", cch)[1])[0].c_str());
									std::string filename = "./config/itemDB.json";
									// Membaca file JSON
									json jsonData;
									std::ifstream configFile(filename);
									configFile >> jsonData;
									configFile.close();

									if (jsonData.find(choose_item_type) != jsonData.end()) {
										// Pastikan variabel itemid dan hfar sudah diinisialisasi dengan benar

										// Mengubah nilai "far" dengan menggunakan itemid sebagai kunci
										jsonData[choose_item_type]["itemid"] = choose_item_id;

										// Menulis kembali ke file JSON
										std::ofstream outFile(filename);
										outFile << std::setw(4) << jsonData; // Format dengan indentasi 4 spasi
										outFile.close();
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("`2[`9Succes change item type " + std::string(choose_item_type) + " To ItemID" + to_string(choose_item_id));
										p.CreatePacket(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert(string(choose_item_type) + " undefined");
										p.CreatePacket(peer);
									}
								}

								// file redeem code
								if (cch.find("buttonClicked|add_redeem_type") != string::npos) {
									DialogBuilder item;
									item.add_label_icon(true, 32, "`cRedeem code setting``")
										.add_smalltext("NOTE: IT WILL CHANGE IN FILE redeemDB ")
										.add_spacer(false);

									std::ifstream configFile("./config/redeemDB.json");
									if (!configFile.is_open()) {
										std::cout << "Failed to open redeemDB.json" << std::endl;
									}
									else {
										nlohmann::json redeemData;
										configFile >> redeemData;
										configFile.close();

										for (const auto& entry : redeemData.items()) {
											std::string text = entry.key();
											int itemid = entry.value()["itemid"];
											int count = entry.value()["count"];
											item.add_smalltext(text)
												.add_smalltext("itemid: " + to_string(itemid))
												.add_smalltext("count: " + to_string(count))
												.add_spacer(false);
										}
									}
									item.add_spacer(false)
										.add_smalltext(std::string(item_text))
										.add_text_input(6, "add_redeem_type", "`9add code:", "")
										.add_spacer(false)
										.add_smalltext(std::string("itemid_text"))
										.add_text_input(6, "add_redeem_id", "`9ItemID:", "")
										.add_spacer(false)
										.add_smalltext(std::string("count_text"))
										.add_text_input(6, "add_redeem_count", "`9Count:", "")
										.add_spacer(false)
										.add_button("go_add_redeem_type", "`2Change!")
										.end_dialog("item_dialog", "Cancel", "");

									enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(item.to_string()).pack());
								}
								if (cch.find("buttonClicked|remove_redeem_type") != string::npos) {
									DialogBuilder item;
									item.add_label_icon(true, 32, "`cRedeem code setting``")
										.add_smalltext("NOTE: IT WILL CHANGE IN FILE redeemDB ")
										.add_spacer(false);

									std::ifstream configFile("./config/redeemDB.json");
									if (!configFile.is_open()) {
										std::cout << "Failed to open redeemDB.json" << std::endl;
									}
									else {
										nlohmann::json redeemData;
										configFile >> redeemData;
										configFile.close();

										for (const auto& entry : redeemData.items()) {
											std::string text = entry.key();
											int itemid = entry.value()["itemid"];
											int count = entry.value()["count"];
											item.add_smalltext(text)
												.add_smalltext("itemid: " + to_string(itemid))
												.add_smalltext("count: " + to_string(count))
												.add_spacer(false);
										}
									}
									item.add_spacer(false)
										.add_smalltext(std::string(item_text))
										.add_text_input(6, "add_redeem_type", "`9code:", "")
										.add_spacer(false)
										.add_button("go_remove_redeem_type", "`2Remove!")
										.end_dialog("item_dialog", "Cancel", "");

									enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(item.to_string()).pack());
								}
								if (cch.find("buttonClicked|go_add_redeem_type") != string::npos) {
									string choose_redeem_type = explode("\n", explode("add_redeem_type|", cch)[1])[0];
									int choose_redeem_id = atoi(explode("\n", explode("add_redeem_id|", cch)[1])[0].c_str());
									int choose_redeem_count = atoi(explode("\n", explode("add_redeem_count|", cch)[1])[0].c_str());
									std::string filename = "./config/redeemDB.json";

									// Membaca file JSON
									json jsonData;
									std::ifstream configFile(filename);
									configFile >> jsonData;
									configFile.close();

									// Create a new JSON object for the new entry
									json newEntry;
									newEntry["itemid"] = choose_redeem_id;
									newEntry["count"] = choose_redeem_count;

									// Append the new entry to the JSON data using the chosen type as the key
									jsonData[choose_redeem_type] = newEntry;

									// Menulis kembali ke file JSON
									std::ofstream outFile(filename);
									outFile << std::setw(4) << jsonData; // Format dengan indentasi 4 spasi
									outFile.close();

									gamepacket_t p;
									p.Insert("OnTextOverlay");
									p.Insert("`2[`9Succes add redeem code`2]");
									p.CreatePacket(peer);
								}
								if (cch.find("buttonClicked|go_remove_redeem_type") != string::npos) {
									string choose_redeem_type = explode("\n", explode("add_redeem_type|", cch)[1])[0];
									std::string filename = "./config/redeemDB.json";
									// Membaca file JSON
									json jsonData;
									std::ifstream configFile(filename);
									configFile >> jsonData;
									configFile.close();

									// Check if the chosen type exists in the JSON data
									if (jsonData.find(choose_redeem_type) != jsonData.end()) {
										// Remove the chosen type from the JSON data
										jsonData.erase(choose_redeem_type);

										// Menulis kembali ke file JSON
										std::ofstream outFile(filename);
										outFile << std::setw(4) << jsonData; // Format dengan indentasi 4 spasi
										outFile.close();

										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("`2[`9Succes remove item type " + std::string(choose_redeem_type));
										p.CreatePacket(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("wrong code");
										p.CreatePacket(peer);
									}
								}

								// file newget
								if (cch.find("buttonClicked|change_get_type") != string::npos) {
									DialogBuilder item;
									item.add_label_icon(true, 32, "`cget type setting``")
										.add_smalltext("NOTE: IT WILL CHANGE IN FILE newgetDB ")
										.add_spacer(false);
									for (int i = 1; i < 6; i++) {
										std::ifstream configFile("./config/newgetDB.json");
										if (!configFile.is_open()) {
											std::cout << "Failed to open config.json" << std::endl;

										}
										nlohmann::json config;
										configFile >> config;
										configFile.close();
										string text = "item_" + to_string(i);
										int itemid = config[text]["itemid"].get<int>();
										int count = config[text]["count"].get<int>();
										// + " (" + items.at(itemid).name + ")"
										item.add_smalltext(string(text))
											.add_smalltext("itemid: " + to_string(itemid))
											.add_smalltext("count: " + to_string(count))
											.add_spacer(false);
									}
									item.add_spacer(false)
										.add_smalltext(std::string(item_text))
										.add_text_input(7, "choose_get_type", "`9Item type:", "item_1")
										.add_spacer(false)
										.add_smalltext(std::string(itemid_text))
										.add_text_input(6, "choose_get_id", "`9ItemID:", "")
										.add_spacer(false)
										.add_smalltext(std::string(itemid_text))
										.add_text_input(6, "choose_get_count", "`9Count:", "")
										.add_spacer(false)
										.add_button("go_change_get_type", "`2Change!")
										.end_dialog("item_dialog", "Cancel", "");
									enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(item.to_string()).pack());
								}
								if (cch.find("buttonClicked|go_change_get_type") != string::npos) {
									string choose_get_type = explode("\n", explode("choose_get_type|", cch)[1])[0];
									int choose_get_id = atoi(explode("\n", explode("choose_get_id|", cch)[1])[0].c_str());
									int choose_get_count = atoi(explode("\n", explode("choose_get_count|", cch)[1])[0].c_str());
									std::string filename = "./config/newgetDB.json";
									// Membaca file JSON
									json jsonData;
									std::ifstream configFile(filename);
									configFile >> jsonData;
									configFile.close();

									if (jsonData.find(choose_get_type) != jsonData.end()) {
										// Pastikan variabel itemid dan hfar sudah diinisialisasi dengan benar

										// Mengubah nilai "far" dengan menggunakan itemid sebagai kunci
										jsonData[choose_get_type]["itemid"] = choose_get_id;
										jsonData[choose_get_type]["count"] = choose_get_count;

										// Menulis kembali ke file JSON
										std::ofstream outFile(filename);
										outFile << std::setw(4) << jsonData; // Format dengan indentasi 4 spasi
										outFile.close();
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("`2[`9Succes change item type " + std::string(choose_get_type) + " To ItemID" + to_string(choose_get_id));
										p.CreatePacket(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert(string(choose_get_type) + " undefined");
										p.CreatePacket(peer);
									}
								}

								// file drop item tupe
								if (cch.find("buttonClicked|drop_item_type") != string::npos) {
									DialogBuilder item;
									item.add_label_icon(true, 32, "`cItem type setting``")
										.add_smalltext("NOTE: IT WILL CHANGE IN FILE blockDB ");
									for (int i = 1; i < 3; i++) {
										std::ifstream configFile("./config/blockDB.json");
										if (!configFile.is_open()) {
											std::cout << "Failed to open config.json" << std::endl;

										}
										nlohmann::json config;
										configFile >> config;
										configFile.close();
										string text = "item_" + to_string(i);
										int itemid = config[text]["itemid"].get<int>();
										item.add_smalltext(string(text) + ": " + to_string(itemid) + "(" + items.at(itemid).name + ")");
									}
									item.add_spacer(false)
										.add_smalltext(std::string(item_text))
										.add_text_input(7, "drop_choose_item_type", "`9Item type:", "item_1")
										.add_spacer(false)
										.add_smalltext(std::string(itemid_text))
										.add_text_input(6, "drop_choose_item_id", "`9ItemID:", "")
										.add_spacer(false)
										.add_button("go_drop_type", "`2Change!")
										.end_dialog("item_dialog", "Cancel", "");
									enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(item.to_string()).pack());
								}
								if (cch.find("buttonClicked|go_drop_type") != string::npos) {
									string drop_choose_item_type = explode("\n", explode("drop_choose_item_type|", cch)[1])[0];
									int drop_choose_item_id = atoi(explode("\n", explode("drop_choose_item_id|", cch)[1])[0].c_str());
									std::string filename = "./config/blockDB.json";
									// Membaca file JSON
									json jsonData;
									std::ifstream configFile(filename);
									configFile >> jsonData;
									configFile.close();

									if (jsonData.find(drop_choose_item_type) != jsonData.end()) {
										// Pastikan variabel itemid dan hfar sudah diinisialisasi dengan benar

										// Mengubah nilai "far" dengan menggunakan itemid sebagai kunci
										jsonData[drop_choose_item_type]["itemid"] = drop_choose_item_id;

										// Menulis kembali ke file JSON
										std::ofstream outFile(filename);
										outFile << std::setw(4) << jsonData; // Format dengan indentasi 4 spasi
										outFile.close();
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("`2[`9Succes change item type " + std::string(drop_choose_item_type) + " To ItemID" + to_string(drop_choose_item_id));
										p.CreatePacket(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert(string(drop_choose_item_type) + " undefined");
										p.CreatePacket(peer);
									}
								}

								// file change gem
								if (cch.find("buttonClicked|change_gem") != string::npos) {
									DialogBuilder item;
									item.add_label_icon(true, 32, "`cMultiple gem item setting``")
										.add_smalltext("NOTE: IT WILL CHANGE IN FILE itemDB ")
										.add_spacer(false)
										.add_smalltext(std::string(item_text))
										.add_text_input(6, "gems_item_type", "`2Item type: ", "item_2")
										.add_spacer(false)
										.add_smalltext(std::string(gems_text))
										.add_text_input(6, "count_gems", "(x) gems:", "")
										.add_spacer(false)
										.add_button("go_change_gems", "`2Change!")
										.end_dialog("item_dialog", "Cancel", "");
									enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(item.to_string()).pack());
								}
								if (cch.find("buttonClicked|go_change_gems") != string::npos) {
									string gems_item_type = explode("\n", explode("gems_item_type|", cch)[1])[0];
									int count_gems = atoi(explode("\n", explode("count_gems|", cch)[1])[0].c_str());
									std::string filename = "./config/itemDB.json";

									json jsonData;
									std::ifstream configFile(filename);
									configFile >> jsonData;
									configFile.close();

									if (count_gems > 0) {
										if (jsonData.find(gems_item_type) != jsonData.end()) {

											jsonData[gems_item_type]["gems"] = count_gems;

											std::ofstream outFile(filename);
											outFile << std::setw(4) << jsonData;
											outFile.close();
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert("`2[`9Succes change item id " + string(gems_item_type) + " To " + to_string(count_gems) + " (x) gems");
											p.CreatePacket(peer);
										}
										else {
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert(string(gems_item_type) + " undefined");
											p.CreatePacket(peer);
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("`2[`9Multiple Gems Must > 0");
										p.CreatePacket(peer);
									}
								}

								// file hit
								if (cch.find("buttonClicked|change_hit") != string::npos) {
									DialogBuilder item;
									item.add_label_icon(true, 32, "`cHit count setting``")
										.add_smalltext("NOTE: IT WILL CHANGE IN FILE itemDB ")
										.add_spacer(false)
										.add_smalltext(std::string(item_text))
										.add_text_input(7, "hit_item_type", "`2Item type:", "item_1")
										.add_spacer(false)
										.add_smalltext(std::string(hit_text))
										.add_text_input(6, "count_hit", "hit:", "")
										.add_spacer(false)
										.add_button("go_change_hit", "`2Change!")
										.end_dialog("item_dialog", "Cancel", "");
									enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(item.to_string()).pack());
								}
								if (cch.find("buttonClicked|go_change_hit") != string::npos) {
									string hit_item_type = explode("\n", explode("hit_item_type|", cch)[1])[0];
									int count_hit = atoi(explode("\n", explode("count_hit|", cch)[1])[0].c_str());
									std::string filename = "./config/itemDB.json";
									// Membaca file JSON
									json jsonData;
									std::ifstream configFile(filename);
									configFile >> jsonData;
									configFile.close();
									if (count_hit > 0) {
										// Memeriksa apakah "hit" ada dalam file JSON
										if (jsonData.find(hit_item_type) != jsonData.end()) {
											// Pastikan variabel itemid dan hfar sudah diinisialisasi dengan benar

											// Mengubah nilai "hit" dengan menggunakan itemid sebagai kunci
											jsonData[hit_item_type]["hit"] = count_hit;

											// Menulis kembali ke file JSON
											std::ofstream outFile(filename);
											outFile << std::setw(4) << jsonData; // Format dengan indentasi 4 spasi
											outFile.close();
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert("`2[`9Succes change item id " + string(hit_item_type) + " To " + to_string(count_hit) + " (x) gems");
											p.CreatePacket(peer);
										}
										else {
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert(string(hit_item_type) + " undefined");
											p.CreatePacket(peer);
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("`2[`9Hit must > 0`2]");
										p.CreatePacket(peer);
									}
								}

								// change drop
								if (cch.find("buttonClicked|change_drop") != string::npos) {
									DialogBuilder item;
									item.add_label_icon(true, 32, "`cdrop item setting``")
										.add_smalltext("NOTE: IT WILL CHANGE IN FILE BlockDB ")
										.add_spacer(false)
										.add_smalltext(std::string(item_text))
										.add_text_input(7, "drop_item_type", "item type:", "item_1")
										.add_spacer(false)
										.add_smalltext(drop_prize_text)
										.add_text_input(6, "prize", "prize :", "")
										.add_spacer(false)
										.add_smalltext(drop_count_text)
										.add_text_input(6, "count", "count :", "")
										.add_spacer(false)
										.add_button("go_change_drop", "`2Change!")
										.end_dialog("item_dialog", "Cancel", "");
									enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(item.to_string()).pack());
								}
								if (cch.find("buttonClicked|go_change_drop") != string::npos) {
									string drop_item_type = explode("\n", explode("drop_item_type|", cch)[1])[0];
									int prize = atoi(explode("\n", explode("prize|", cch)[1])[0].c_str());
									int count = atoi(explode("\n", explode("count|", cch)[1])[0].c_str());
									std::string filename = "./config/blockDB.json";
									// Membaca file JSON
									json jsonData;
									std::ifstream configFile(filename);
									configFile >> jsonData;
									configFile.close();

									// Memeriksa apakah "far" ada dalam file JSON
									if (jsonData.find(drop_item_type) != jsonData.end()) {
										// Pastikan variabel itemid dan hfar sudah diinisialisasi dengan benar

										// Mengubah nilai "far" dengan menggunakan itemid sebagai kunci
										jsonData[drop_item_type]["prize"] = prize;
										jsonData[drop_item_type]["count"] = count;

										// Menulis kembali ke file JSON
										std::ofstream outFile(filename);
										outFile << std::setw(4) << jsonData; // Format dengan indentasi 4 spasi
										outFile.close();
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("`2[`9Succes change item id " + std::string(drop_item_type) + " To " + to_string(prize) + " (x) gems");
										p.CreatePacket(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert(string(drop_item_type + "undefined"));
										p.CreatePacket(peer);
									}
								}

								if (cch.find("buttonClicked|change_far") != string::npos) {
									DialogBuilder item;
									item.add_label_icon(true, 32, "`cFar Item setting``")
										.add_smalltext("NOTE: IT WILL CHANGE IN FILE itemDB ")
										.add_spacer(false)
										.add_smalltext(std::string(item_text))
										.add_text_input(7, "far_item_type", "`2Item type:", "item_1")
										.add_spacer(false)
										.add_smalltext(std::string(far_text))
										.add_text_input(6, "count_far", "Far:", "")
										.add_spacer(false)
										.add_button("go_change_far", "`2Change!")
										.end_dialog("item_dialog", "Cancel", "");
									enet_peer_send(peer, 0, Variant{ "OnDialogRequest" }.push(item.to_string()).pack());
								}
								if (cch.find("buttonClicked|go_change_far") != string::npos) {
									string far_item_type = explode("\n", explode("far_item_type|", cch)[1])[0];
									int count_far = atoi(explode("\n", explode("count_far|", cch)[1])[0].c_str());
									std::string filename = "./config/itemDB.json";
									json jsonData;
									std::ifstream configFile(filename);
									configFile >> jsonData;
									configFile.close();

									if (count_far > 0) {
										if (jsonData.find(far_item_type) != jsonData.end()) {
											jsonData[far_item_type]["far"] = count_far;

											std::ofstream outFile(filename);
											outFile << std::setw(4) << jsonData;
											outFile.close();
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert("`2[`9Succes change item type " + std::string(far_item_type) + " To " + to_string(count_far) + " Far");
											p.CreatePacket(peer);
										}
										else {
											gamepacket_t p;
											p.Insert("OnTextOverlay");
											p.Insert(string(far_item_type) + " undefined");
											p.CreatePacket(peer);
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnTextOverlay");
										p.Insert("`2[`9Far Must > 0`2]");
										p.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch.find("action|friends") != string::npos) {
								send_social(peer);
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|socialportal\nbuttonClicked|tradehistory\n\n") {
								string trade_logs = "";
								for (int i = 0; i < pInfo(peer)->trade_logs.size(); i++) trade_logs += "\nadd_spacer|small|\nadd_smalltext|" + pInfo(peer)->trade_logs[i] + "|left|";
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|small|" + pInfo(peer)->tankIDName + "'s Trade History|left|242|" + (pInfo(peer)->trade_logs.size() == 0 ? "\nadd_spacer|small|\nadd_smalltext|Nothing to show yet.|left|" : trade_logs) + "\nadd_spacer|small|\nadd_button|socialportal|Back|noflags|0|0|\nadd_button||Close|noflags|0|0|\nadd_quick_exit|\nend_dialog|playerportal|||");
								p.CreatePacket(peer);
						}
							else if (cch == "action|battlepasspopup\n") {
							gamepacket_t p(550);
							p.Insert("OnDialogRequest");
							int growpassid = 6124;
							if (today_day == pInfo(peer)->gd) growpassid = 6292;
							if (pInfo(peer)->gp == 1) p.Insert("set_default_color|`o\nadd_label_with_icon|big|Grow Pass Rewards|left|9222|\nadd_smalltext|`9You can claim your daily reward everyday here.``|left|\nadd_button_with_icon|claim_reward||staticBlueFrame|" + to_string(growpassid) + "||\nadd_button_with_icon|claim_reward||staticBlueFrame|" + to_string(growpassid) + "||\nadd_button_with_icon|claim_reward||staticBlueFrame|" + to_string(growpassid) + "||\nadd_button_with_icon|claim_reward||staticBlueFrame|" + to_string(growpassid) + "||\nadd_button_with_icon|claim_reward||staticBlueFrame|" + to_string(growpassid) + "||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nend_dialog|worlds_list||Back|\nadd_quick_exit|\n");
							else p.Insert("set_default_color|`o\nadd_label_with_icon|big|Grow Pass Rewards|left|9222|\nadd_button|deposit|`2Purchase``|noflags|0|0|\nadd_smalltext|`4You must purchase the Grow Pass role to claim your prize!``|left|\nadd_button_with_icon|||staticBlueFrame|" + to_string(growpassid) + "||\nadd_button_with_icon|||staticBlueFrame|" + to_string(growpassid) + "||\nadd_button_with_icon|||staticBlueFrame|" + to_string(growpassid) + "||\nadd_button_with_icon|||staticBlueFrame|" + to_string(growpassid) + "||\nadd_button_with_icon|||staticBlueFrame|" + to_string(growpassid) + "||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nend_dialog|||Back|\nadd_quick_exit|\n");
							p.CreatePacket(peer);
							break;
							}
							else if (cch == "action|storenavigate\nitem|main\nselection|deposit\n" || cch == "action|storenavigate\nitem|locks\nselection|upgrade_backpack\n" || cch == "action|storenavigate\nitem|main\nselection|bonanza\n" || cch == "action|storenavigate\nitem|main\nselection|calendar\n" || cch == "action|store\nlocation|bottommenu\n" || cch == "action|store\nlocation|gem\n" || cch == "action|store\nlocation|pausemenu\n" || cch == "action|storenavigate\nitem|main\nselection|gems_rain\n") {
							if (cch == "action|store\nlocation|bottommenu\n" || cch == "action|store\nlocation|gem\n" || cch == "action|store\nlocation|pausemenu\n") shop_tab(peer, "tab1");
							if (cch == "action|storenavigate\nitem|main\nselection|gems_rain\n") shop_tab(peer, "tab1_1");
							if (cch == "action|storenavigate\nitem|main\nselection|calendar\n") shop_tab(peer, "tab1_2");
							if (cch == "action|storenavigate\nitem|main\nselection|bonanza\n")	shop_tab(peer, "tab1_3");
							if (cch == "action|storenavigate\nitem|locks\nselection|upgrade_backpack\n") shop_tab(peer, "tab2_1");
							if (cch == "action|storenavigate\nitem|main\nselection|deposit\n") SendCmd(peer, "/deposit", true);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|advbegins\nnameEnter|") != string::npos) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
									if (block_->fg == 4722) {
										if (block_access(peer, world_, block_)) {
											string text = cch.substr(53, cch.length() - 54).c_str();
											if (text.size() > 32) break;
											block_->heart_monitor = text;
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID), p.Insert("Updated adventure!"), p.Insert(0), p.Insert(0), p.CreatePacket(peer);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(peer)->world != pInfo(currentPeer)->world or pInfo(currentPeer)->adventure_begins == false) continue;
												pInfo(currentPeer)->adventure_begins = false;
											}
										}
									}
								}
								break;
						}
							else if (cch.find("action|buy") != string::npos) {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 3) break;
								string item = explode("\n", t_[2])[0];
								int price = 0, free = get_free_slots(pInfo(peer)), slot = 1, getcount = 0, get_counted = 0, random_pack = 0, token = 0;
								gamepacket_t p2;
								p2.Insert("OnStorePurchaseResult");
								if (item == "main") shop_tab(peer, "tab1");
								else if (item == "locks") shop_tab(peer, "tab2");
								else if (item == "itempack") shop_tab(peer, "tab3");
								else if (item == "bigitems") shop_tab(peer, "tab4");
								else if (item == "weather") shop_tab(peer, "tab5");
								else if (item == "token") shop_tab(peer, "tab6");
								else if (item == "systemcoin") c_daily(peer, true, "tab_1", 0);
								else if (item == "upgrade_backpack") {
									price = 100 * ((((pInfo(peer)->inv.size() - 17) / 10) * ((pInfo(peer)->inv.size() - 17) / 10)) + 1);
									if (price > pInfo(peer)->gems) {
										packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
										p2.Insert("You can't afford `0Upgrade Backpack`` (`w10 Slots``)!  You're `$" + setGems(price - pInfo(peer)->gems) + "`` Gems short.");
									}
									else {
										if (pInfo(peer)->inv.size() < 496) {
											{
												gamepacket_t p;
												p.Insert("OnConsoleMessage");
												p.Insert("You've purchased `0Upgrade Backpack`` (`010 Slots``) for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems - price) + "`` Gems left.");
												p.CreatePacket(peer);
											}
											p2.Insert("You've purchased `0Upgrade Backpack (10 Slots)`` for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems - price) + "`` Gems left.\n\n`5Received: ```0Backpack Upgrade``\n");
											{
												packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
												gamepacket_t p;
												p.Insert("OnSetBux");
												p.Insert(pInfo(peer)->gems -= price), p.Insert(0), p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
												if (pInfo(peer)->supp >= 2) {
													p.Insert((float)33796, (float)1, (float)0);
												}
												p.CreatePacket(peer);
											}
											for (int i_ = 0; i_ < 10; i_++) { // default inv dydis
												Items itm_{};
												itm_.id = 0, itm_.count = 0;
												pInfo(peer)->inv.push_back(itm_);
											}
											send_inventory(peer);
											update_clothes(peer);
											shop_tab(peer, "tab2");
										}
									}
									p2.CreatePacket(peer);
								}
								else {
									vector<int> list;
									vector<vector<int>> itemai;
									string item_name = "";
									ifstream ifs("database/shop/-" + item + ".json");
									if (ifs.is_open()) {
										json j;
										ifs >> j;
										price = j["g"].get<int>();
										item_name = j["p"].get<string>();
										if (j.find("itemai") != j.end()) { // mano sistema
											if (pInfo(peer)->gems < price) {
												packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
												p2.Insert("You can't afford `o" + item_name + "``!  You're `$" + setGems(price - pInfo(peer)->gems) + "`` Gems short."), p2.CreatePacket(peer);
												break;
											}
											itemai = j["itemai"].get<vector<vector<int>>>();
											int reik_slots = itemai.size();
											int turi_slots = get_free_slots(pInfo(peer));
											for (vector<int> item_info : itemai) {
												int turi_dabar = 0;
												modify_inventory(peer, item_info[0], turi_dabar);
												if (turi_dabar != 0) reik_slots--;
												if (turi_dabar + item_info[1] > 200) goto fail;
											}
											if (turi_slots < reik_slots) goto fail;
											{
												//if (item == "g4good_Gem_Charity") grow4good(peer, false, "donate_gems", 0);
												//if (item != "arm_guy" and item != "g4good_Gem_Charity") grow4good(peer, false, "gems", price);
												pInfo(peer)->gems -= price;
												gamepacket_t gem_upd;
												gem_upd.Insert("OnSetBux"), gem_upd.Insert(pInfo(peer)->gems), gem_upd.Insert(0), gem_upd.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
												if (pInfo(peer)->supp >= 2) {
													gem_upd.Insert((float)33796, (float)1, (float)0);
												}
												gem_upd.CreatePacket(peer);
												vector<string> received_items{}, received_items2{};
												for (vector<int> item_info : itemai) {
													uint32_t item_id = item_info[0];
													int item_count = item_info[1];
													modify_inventory(peer, item_id, item_count);
													received_items.push_back("Got " + to_string(item_info[1]) + " `#" + items[item_id].ori_name + "``."), received_items2.push_back(to_string(item_info[1]) + " " + items[item_id].ori_name);
												}
												packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
												//if (item == "arm_guy") grow4good(peer, false, "purchase_waving", 0);
												gamepacket_t p_;
												p_.Insert("OnConsoleMessage"), p_.Insert("You've purchased `o" + item_name + "`` for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems) + "`` Gems left." + "\n" + join(received_items, "\n")), p_.CreatePacket(peer);
												p2.Insert("You've purchased `o" + item_name + "`` for `$" + setGems(price) + "`` Gems.\nYou have `$" + setGems(pInfo(peer)->gems) + "`` Gems left." + "\n\n`5Received: ``" + join(received_items2, ", ") + "\n"), p2.CreatePacket(peer);
												break;
											}
										fail:
											packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
											p2.Insert("You don't have enough space in your inventory to buy that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
											p2.CreatePacket(peer);
											break;
										}
										list = j["i"].get<vector<int>>();
										getcount = j["h"].get<int>();
										get_counted = j["h"].get<int>();
										slot = j["c"].get<int>();
										token = j["t"].get<int>();
										random_pack = j["random"].get<int>();
										int totaltoken = 0, tokencount = 0, mega_token = 0, inventoryfull = 0;
										modify_inventory(peer, 1486, tokencount);
										modify_inventory(peer, 6802, mega_token);
										totaltoken = tokencount + (mega_token * 100);
										vector<pair<int, int>> receivingitems;
										if (token == 0 ? price > pInfo(peer)->gems : token > totaltoken) {
											packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
											p2.Insert("You can't afford `o" + item_name + "``!  You're `$" + (token == 0 ? "" + setGems(price - pInfo(peer)->gems) + "`` Gems short." : "" + setGems(token - totaltoken) + "`` Growtokens short."));
										}
										else {
											if (free >= slot) {
												string received = "", received2 = "";
												if (item == "basic_splice") {
													slot++;
													receivingitems.push_back(make_pair(11, 10));
												}
												if (item == "race_packa") {
													slot++;
													receivingitems.push_back(make_pair(11, 10));
												}
												for (int i = 0; i < slot; i++) receivingitems.push_back(make_pair((random_pack == 1 ? list[rand() % list.size()] : list[i]), getcount));
												for (int i = 0; i < slot; i++) {
													int itemcount = 0;
													modify_inventory(peer, receivingitems[i].first, itemcount);
													if (itemcount + getcount > 200) inventoryfull = 1;
												}
												if (inventoryfull == 0) {
													int i = 0;
													for (i = 0; i < slot; i++) {
														received += (i != 0 ? ", " : "") + items[receivingitems[i].first].name;
														received2 += "Got " + to_string(receivingitems[i].second) + " `#" + items[receivingitems[i].first].name + "``." + (i == (slot - 1) ? "" : "\n") + "";
														modify_inventory(peer, receivingitems[i].first, receivingitems[i].second);
													}
												}
												else {
													packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
													p2.Insert("You don't have enough space in your inventory that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
													p2.CreatePacket(peer);
													break;
												}
												{
													gamepacket_t p;
													p.Insert("OnConsoleMessage");
													p.Insert("You've purchased `o" + received + "`` for `$" + (token == 0 ? "" + setGems(price) + "`` Gems." : "" + setGems(token) + "`` Growtokens.") + "\nYou have `$" + (token == 0 ? "" + setGems(pInfo(peer)->gems - price) + "`` Gems left." : "" + setGems(totaltoken - token) + "`` Growtokens left.") + "\n" + received2);
													p.CreatePacket(peer);
												}
												p2.Insert("You've purchased `o" + received + "`` for `$" + (token == 0 ? "" + setGems(price) + "`` Gems." : "" + setGems(token) + "`` Growtokens.") + "\nYou have `$" + (token == 0 ? "" + setGems(pInfo(peer)->gems - price) + "`` Gems left." : "" + setGems(totaltoken - token) + "`` Growtokens left.") + "\n\n`5Received: ``" + (get_counted <= 1 ? "" : "`0" + to_string(get_counted)) + "`` " + received + "\n"), p2.CreatePacket(peer);
												if (token == 0) {
													pInfo(peer)->gems -= price;
													gamepacket_t p;
													p.Insert("OnSetBux");
													p.Insert(pInfo(peer)->gems);
													p.Insert(0);
													p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
													if (pInfo(peer)->supp >= 2) {
														p.Insert((float)33796, (float)1, (float)0);
													}
													p.CreatePacket(peer);
												}
												else {
													if (tokencount >= token) modify_inventory(peer, 1486, token *= -1);
													else {
														modify_inventory(peer, 1486, tokencount *= -1);
														modify_inventory(peer, 6802, mega_token *= -1);
														int givemegatoken = (totaltoken - token) / 100;
														int givetoken = (totaltoken - token) - (givemegatoken * 100);
														modify_inventory(peer, 1486, givetoken);
														modify_inventory(peer, 6802, givemegatoken);
													}
												}
												packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											}
											else {
												packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
												p2.Insert(slot > 1 ? "You'll need " + to_string(slot) + " slots free to buy that! You have " + to_string(free) + " slots." : "You don't have enough space in your inventory that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
											}
										}
									}
									else {
										packet_(peer, "action|play_sfx\nfile|audio/bleep_fail.wav\ndelayMS|0");
										p2.Insert("This item was not found. Server error.");
										p2.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch == "action|AccountSecurity\nlocation|pausemenu\n") {
								gamepacket_t p(500);
								p.Insert("OnDialogRequest");
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wAdvanced Account Protection ``|left|3732|\nadd_textbox|`1You are about to enable the Advanced Account Protection.``|left|\nadd_textbox|`1After that, every time you try to log in from a new device and IP you will receive an email with a login confirmation link.``|left|\nadd_textbox|`1This will significantly increase your account security.``|left|\nend_dialog|secureaccount|Cancel|Ok|");
								p.CreatePacket(peer);
								break;
							}
							else if (cch.find("action|respawn") != string::npos) SendRespawn(peer, false, 0, (cch.find("action|respawn_spike") != string::npos) ? false : true);
							else if (cch == "action|refresh_item_data\n") {
							if (pInfo(peer)->world.empty()) {
								save_player(pInfo(peer), (f_saving_ ? false : true));
								enet_peer_send(peer, 0, enet_packet_create(item_data, item_data_size + 60, ENET_PACKET_FLAG_RELIABLE));
								enet_peer_disconnect_later(peer, 0);
							}
							else writelogd(pInfo(peer)->tankIDName + " tried to disconnent while in world");
							break;
							}
							else if (cch == "action|enter_game\n") {
								ifstream verify("database/verify/" + pInfo(peer)->rid + ".json");
								if (verify.is_open()) {
									json j;
									verify >> j;
									pInfo(peer)->is_verified = j["verified_status"].get<bool>();
								}
								if (pInfo(peer)->is_verified == false) {
									string dialogs = "set_default_color|`o|\n";
									dialogs += "add_label_with_icon|big|`$Verify your device!|left|32|\n";
									dialogs += "add_smalltext|`oWe've detected new device location from your device!|\n";
									dialogs += "add_spacer|small|\nadd_label_with_icon|small|`#Moderator: `oHello. Im a Moderator on this servers, i don't recommend you to use illegal powerkuy/genta on this server.|left|4358|\n";
									dialogs += "add_spacer|small|\nadd_smalltext|`oPlease click `5Verify `oto registered your new device location!|";
									dialogs += "\nend_dialog|verify_me|`wCancel|`wVerify|";
									gamepacket_t packet;
									packet.Insert("OnDialogRequest");
									packet.Insert(dialogs), packet.CreatePacket(peer);
									break;
								}
								pInfo(peer)->enter_game++;
								if (pInfo(peer)->world == "" && pInfo(peer)->enter_game == 1) {
									if (pInfo(peer)->tankIDName.empty()) {
										gamepacket_t p;
										p.Insert("OnDialogRequest"), p.Insert(r_dialog("")), p.CreatePacket(peer);
									}
									else {
										pInfo(peer)->tmod = pInfo(peer)->mod;
										pInfo(peer)->name_color = (pInfo(peer)->admin == 1 ? admin_color : pInfo(peer)->founder == 1 ? founder_color : pInfo(peer)->owner == 1 ? own_color : pInfo(peer)->ultramod == 1 ? ultramod_color : pInfo(peer)->vip == 1 ? vip_color : pInfo(peer)->superdev == 1 ? smod_color : pInfo(peer)->dev == 1 ? royal_color : (pInfo(peer)->tmod == 1) ? mod_color : "`0");
										pInfo(peer)->modName = (pInfo(peer)->admin == 1 ? admin_color : pInfo(peer)->founder == 1 ? founder_color : pInfo(peer)->owner == 1 ? own_color : pInfo(peer)->superdev == 1 ? smod_color + pInfo(peer)->tankIDName : pInfo(peer)->dev == 1 ? royal_color + pInfo(peer)->tankIDName : (pInfo(peer)->tmod == 1 ? mod_color + pInfo(peer)->tankIDName : "`0" + pInfo(peer)->tankIDName));
										string thetag = (pInfo(peer)->mod || pInfo(peer)->dev ? "@" : "");
										if (pInfo(peer)->drt) pInfo(peer)->d_name = (pInfo(peer)->drt ? "`4" + thetag : pInfo(peer)->name_color) + (pInfo(peer)->drt ? "Dr." : "") + pInfo(peer)->tankIDName + (pInfo(peer)->is_legend ? " of Legend" : "");
										int on_ = 0, t_ = 0;
										//if (gotall) pInfo(peer)->superdev = 1, pInfo(peer)->dev = 1, pInfo(peer)->mod = 1, pInfo(peer)->gems = 999999, pInfo(peer)->gtwl = 99999;
										vector<string> friends_;
										for (int c_ = 0; c_ < pInfo(peer)->friends.size(); c_++) friends_.push_back(pInfo(peer)->friends[c_].name);
										if (not pInfo(peer)->invis and not pInfo(peer)->m_h) {
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												t_ += 1 + rand() % 3 + 1;
												if (find(friends_.begin(), friends_.end(), pInfo(currentPeer)->tankIDName) != friends_.end()) {
													if (pInfo(currentPeer)->show_friend_notifications_) {
														gamepacket_t p;
														p.Insert("OnConsoleMessage"), p.Insert("`3FRIEND ALERT:`` " + (pInfo(peer)->name_color == "`0" ? "`o" : pInfo(peer)->name_color + "" + pInfo(peer)->tankIDName) + "`` has `2logged on``.");
														packet_(currentPeer, "action|play_sfx\nfile|audio/friend_logon.wav\ndelayMS|0");
														p.CreatePacket(currentPeer);
													}
													on_++;
												}
											}
										}
										{
											gamepacket_t p;
											p.Insert("OnEmoticonDataChanged");
											p.Insert(151749376);
											p.Insert("(wl)|ā|1&(yes)|Ă|1&(no)|ă|1&(love)|Ą|1&(oops)|ą|1&(shy)|Ć|1&(wink)|ć|1&(tongue)|Ĉ|1&(agree)|ĉ|1&(sleep)|Ċ|1&(punch)|ċ|1&(music)|Č|1&(build)|č|1&(megaphone)|Ď|1&(sigh)|ď|1&(mad)|Đ|1&(wow)|đ|1&(dance)|Ē|1&(see-no-evil)|ē|1&(bheart)|Ĕ|1&(heart)|ĕ|1&(grow)|Ė|1&(gems)|ė|1&(kiss)|Ę|1&(gtoken)|ę|1&(lol)|Ě|1&(smile)|Ā|1&(cool)|Ĝ|1&(cry)|ĝ|1&(vend)|Ğ|1&(bunny)|ě|1&(cactus)|ğ|1&(pine)|Ĥ|1&(peace)|ģ|1&(terror)|ġ|1&(troll)|Ġ|1&(evil)|Ģ|1&(fireworks)|Ħ|1&(football)|ĥ|1&(alien)|ħ|1&(party)|Ĩ|1&(pizza)|ĩ|1&(clap)|Ī|1&(song)|ī|1&(ghost)|Ĭ|1&(nuke)|ĭ|1&(halo)|Į|1&(turkey)|į|1&(gift)|İ|1&(cake)|ı|1&(heartarrow)|Ĳ|1&(lucky)|ĳ|1&(shamrock)|Ĵ|1&(grin)|ĵ|1&(ill)|Ķ|1&");
											p.CreatePacket(peer);
										}
										/*
										{
											gamepacket_t p;
											p.Insert("OnEmoticonDataChanged");
											p.Insert(151749376);
											string other = "";
											for (int i = 0; i < pInfo(peer)->gr.size(); i++) other += pInfo(peer)->gr[i];
											p.Insert(other + "" + (pInfo(peer)->supp == 2 ? "(yes)|Ă|1" : "(yes)|Ă|0") + "&" + (pInfo(peer)->supp != 0 ? "(no)|ă|1" : "(no)|ă|0") + "&" + (pInfo(peer)->supp == 2 ? "(love)|Ą|1" : "(love)|Ą|0") + "&" + (pInfo(peer)->supp != 0 ? "(shy)|Ć|1&(wink)|ć|1" : "(shy)|Ć|0&(wink)|ć|0") + "&" + (pInfo(peer)->level >= 5 ? "(tongue)|Ĉ|1" : "(tongue)|Ĉ|0") + "&" + (pInfo(peer)->friends.size() >= 20 ? "(agree)|ĉ|1" : "(agree)|ĉ|0") + "&" + (pInfo(peer)->supp != 0 ? "(music)|Č|1" : "(music)|Č|0") + "&" + (pInfo(peer)->friends.size() >= 50 ? "(build)|č|1" : "(build)|č|0") + "&" + (pInfo(peer)->supp == 2 ? "(megaphone)|Ď|1" : "(megaphone)|Ď|0") + "&" + (pInfo(peer)->level >= 5 ? "(sigh)|ď|1&(mad)|Đ|1&(wow)|đ|1" : "(sigh)|ď|0&(mad)|Đ|0&(wow)|đ|0") + "&" + (pInfo(peer)->friends.size() >= 40 ? "(dance)|Ē|1" : "(dance)|Ē|0") + "&" + (pInfo(peer)->friends.size() >= 30 ? "(see-no-evil)|ē|1" : "(see-no-evil)|ē|0") + "&" + (pInfo(peer)->supp == 2 ? "(heart)|ĕ|1" : "(heart)|ĕ|0") + "&" + (pInfo(peer)->friends.size() >= 10 ? "(kiss)|Ę|1" : "(kiss)|Ę|0") + "&" + (pInfo(peer)->supp != 0 ? "(lol)|Ě|1" : "(lol)|Ě|1") + "&" + (pInfo(peer)->level >= 5 ? "(smile)|Ā|1" : "(smile)|Ā|0") + "&" + (pInfo(peer)->supp == 2 ? "(cool)|Ĝ|1" : "(cool)|Ĝ|0") + "&(lucky)|ĳ|1&");
											p.CreatePacket(peer);
										}*/
										if (pInfo(peer)->ultramod == 1) pInfo(peer)->flagset = 9530;
										if (pInfo(peer)->surgery_type == -1) pInfo(peer)->surgery_type = rand() % 30;
										{
											if (pInfo(peer)->pinata_day != today_day) {
												pInfo(peer)->pinata_prize = false;
												pInfo(peer)->pinata_claimed = false;
											}
											gamepacket_t p;
											p.Insert("OnProgressUISet"), p.Insert(1), p.Insert(0), p.Insert(to_string(pInfo(peer)->pinata_claimed)), p.Insert(1), p.Insert(""), p.Insert(to_string(pInfo(peer)->pinata_prize)), p.CreatePacket(peer);
										}
										if (pInfo(peer)->inventory_sent == false) send_inventory(peer);
										gamepacket_t p1, p2, p3, p4, p5;
										p1.Insert("OnConsoleMessage"), p1.Insert("Welcome back, `w" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "````." + (pInfo(peer)->friends.size() == 0 ? "" : (on_ != 0 ? " `w" + to_string(on_) + "`` friend is online." : " No friends are online."))), p1.CreatePacket(peer);
										p2.Insert("OnAddNotification"), p2.Insert("interface/voucher_icon_overlay.rttex"), p2.Insert("`cWELCOME TO " + server_name + " "), p2.Insert("audio/hub_open.wav"), p2.Insert(0), p2.CreatePacket(peer);
										p3.Insert("OnConsoleMessage"), p3.Insert("`c[+] Welcome To " + server_name + ""), p3.CreatePacket(peer);
										//p4.Insert("OnConsoleMessage"), p4.Insert("`c[+] Server By ItsKyy), p4.CreatePacket(peer);
										//p5.Insert("OnConsoleMessage"), p5.Insert("`c[+] Coded By ItsKyy), p5.CreatePacket(peer);
										{
											/*gamepacket_t p;
											p.Insert("OnConsoleMessage");
											if (thedaytoday == 1) p.Insert("`3Today is Trees Day!`` 50% higher chance to get `2extra block`` from harvesting tree.");
											else if (thedaytoday == 2) p.Insert("`3Today is Breaking Day!`` 15% higher chance to get `2extra seed``.");
											else if (thedaytoday == 3) p.Insert("`3Today is Geiger Day!`` Higher chance of getting a `2better Geiger prize`` & Irradiated mod will last only `210 minutes``.");
											else if (thedaytoday == 4) p.Insert("`3Today is Level Day!`` Get extra `2500 gems`` bonus for leveling up.");
											else if (thedaytoday == 5) p.Insert("`3Today is Gems Day!`` 50% higher chance to get `2extra`` gem drop.");
											else if (thedaytoday == 6) p.Insert("`3Today is Surgery Day!`` Malpractice takes `215 minutes`` and Recovering takes `230 minutes`` & receive `2different prizes``.");
											else if (thedaytoday == 0) p.Insert("`3Today is Fishing Day!`` Catch a fish and receive `2extra lb``.");
											p.CreatePacket(peer);*/
										}
										if (pInfo(peer)->platformid == "0") {
											WindowsAdd += 1;
										}
										if (pInfo(peer)->platformid == "1") {
											iPhoneAdd += 1;
										}
										if (pInfo(peer)->platformid == "2") {
											MacosAdd += 1;
										}
										if (pInfo(peer)->platformid == "3") {
											LinuxAdd += 1;
										}
										if (pInfo(peer)->platformid == "4") {
											AndroidAdd += 1;
										}
										if (pInfo(peer)->platformid == "0,1,1") {
											WindowsAdd += 1;
										}
										char clientConnection[16];
										enet_address_get_host_ip(&peer->address, clientConnection, 16);
										string username = "";
										username = to_lower(pInfo(peer)->tankIDName) + " (" + pInfo(peer)->requestedName + ")";
										cout << "[" << currentDateTime() << "] " << username << " has logged in with IP: " << clientConnection << endl;
										//send_login_player(username, clientConnection);
										ofstream myfile;
										myfile.open("database/loginip/" + to_lower(pInfo(peer)->tankIDName) + ".txt");
										myfile << clientConnection;
										myfile.close();
										p5.Insert("OnConsoleMessage"), p5.Insert("`5Honors are on top! `` Get your new `2honors ``now before someone get it first``"), p5.CreatePacket(peer);
										if (pInfo(peer)->ultramod + pInfo(peer)->owner >= 1) {
											if (get_free_slots(pInfo(peer)) >= 1) {
												if (today_day != pInfo(peer)->mds) {
													pInfo(peer)->mds = today_day;
													vector<int> list2{ 408, 274, 276, 7188 };
													int receive = 1, item = list2[rand() % list2.size()], got = 1;
													modify_inventory(peer, item, receive);
													gamepacket_t p, p2;
													p.Insert("OnConsoleMessage"), p.Insert("Your mod appreciation bonus (feel free keep, trade, or use for prizes) for today is:"), p.CreatePacket(peer);
													p2.Insert("OnConsoleMessage"), p2.Insert("Given `0" + to_string(got) + " " + items[item].name + "``."), p2.CreatePacket(peer);
												}
											}
										}
										world_menu(peer);
										news(peer);
									}
								}
								else enet_peer_disconnect_later(peer, 0);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|dropgay\nbuttonClicked|itsgay") != string::npos) {
								if (pInfo(peer)->dev) {
									gamepacket_t p;
									p.Insert("OnDialogRequest");
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`4Verify Your Action``|left|1432|\nadd_textbox|`0Are you sure want to drop all your items?|left|\nend_dialog|dropall|Nevermind|Yes,iam aure|\n");
									p.CreatePacket(peer);
								}
								else if (pInfo(peer)->dev == 0) {
									packet_(peer, "action|log\nmsg|`4Kontol" + pInfo(peer)->tankIDName + "");
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|dropall") != string::npos) {
								if (pInfo(peer)->dev) {
									packet_(peer, "action|log\nmsg|`4[SYSTEM]`9 :`bSucces `9Drop All `5Items In `2Backpack");
									string recycled = "";
									string name_ = pInfo(peer)->world;
									vector<World>::iterator paa = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									World* world_ = &worlds[paa - worlds.begin()];
									for (int i_ = 0, remove = 0; i_ < pInfo(peer)->inv.size(); i_++) {
										if (items[pInfo(peer)->inv[i_].id].untradeable == 0) {
											remove = pInfo(peer)->inv[i_].count * -1;
											WorldDrop drop_block_{};
											drop_block_.x = (pInfo(peer)->state == 16 ? pInfo(peer)->x - ((rand() % 12) + 18) : pInfo(peer)->x + ((rand() % 12) + 22)), drop_block_.y = pInfo(peer)->y + rand() % 16, drop_block_.id = pInfo(peer)->inv[i_].id, drop_block_.count = pInfo(peer)->inv[i_].count, drop_block_.uid = uint16_t(world_->drop.size()) + 1;
											dropas_(world_, drop_block_);
											recycled += to_string(abs(remove)) + " `w" + items[pInfo(peer)->inv[i_].id].ori_name + "`` Droped.\n";
											modify_inventory(peer, pInfo(peer)->inv[i_].id, remove);
											remove = 0;

										}
										else if (pInfo(peer)->dev == 0) {
											packet_(peer, "action|log\nmsg|`4Kontol" + pInfo(peer)->tankIDName + "");
										}
									}
								}
								break;
							}
							if (cch.find("action|dialog_return\ndialog_name|costum_effect") != string::npos) {
							if (cch.find("buttonClicked|restore_default") != string::npos) {
								pInfo(peer)->hit1 = false;
								pInfo(peer)->punched = 0;
								pInfo(peer)->C_PEffect = 0;
								pInfo(peer)->C_PktType = 0;
								pInfo(peer)->mlgeff = false;
								update_clothes(peer);
							}
							else {
								try {
									if (!is_number(explode("\n", explode("text_input_punchid|", cch)[1])[0])) break;
									if (atoi(explode("\n", explode("text_input_punchid|", cch)[1])[0].c_str()) < 1) break;
									pInfo(peer)->punched = atoi(explode("\n", explode("text_input_punchid|", cch)[1])[0].c_str());

									if (!is_number(explode("\n", explode("text_input_particel1|", cch)[1])[0])) break;
									if (atoi(explode("\n", explode("text_input_particel1|", cch)[1])[0].c_str()) < 1) break;
									pInfo(peer)->C_PEffect = atoi(explode("\n", explode("text_input_particel1|", cch)[1])[0].c_str());

									if (!is_number(explode("\n", explode("text_input_particel2|", cch)[1])[0])) break;
									if (atoi(explode("\n", explode("text_input_particel2|", cch)[1])[0].c_str()) < 17) break;
									if (atoi(explode("\n", explode("text_input_particel2|", cch)[1])[0].c_str()) >= 37) break;
									pInfo(peer)->C_PktType = atoi(explode("\n", explode("text_input_particel2|", cch)[1])[0].c_str());

									pInfo(peer)->hit1 = atoi(explode("\n", explode("checkbox_onehit_true|", cch)[1])[0].c_str()) == 1 ? true : false;

									pInfo(peer)->mlgeff = atoi(explode("\n", explode("checkbox_active_mlgeff|", cch)[1])[0].c_str()) == 1 ? true : false;
									update_clothes(peer);
								}
								catch (...) {
									break;
								}
								enet_peer_send(peer, 0, Variant{ "OnConsoleMessage" }.push("`2Success Setting coyyy..").pack());
							}
							break;
						}
						
							if (cch.find("action|dialog_return\ndialog_name|dialog_cheat_menu") != string::npos) {
							if (cch.find("buttonClicked|restore_default") != string::npos) {
								pInfo(peer)->Cheat_AB = false;
								pInfo(peer)->Cheat_AF = false;
								pInfo(peer)->god_speed = false;
								pInfo(peer)->Cheat_HideOther = false;
								pInfo(peer)->Cheat_HideChat = false;
								pInfo(peer)->JumpCheat = 0;
								pInfo(peer)->cheat_kick = 0;
								pInfo(peer)->cheat_ban = 0;
								pInfo(peer)->Cheat_AF_PunchX = 0;
								pInfo(peer)->Cheat_AF_PunchY = 0;
								pInfo(peer)->Cheat_AF_PlantingTree = 0;
								pInfo(peer)->Cheat_AF_isRunning = false;
								pInfo(peer)->isFacingLeft = false;
								pInfo(peer)->Cheat_Spam = false;
								pInfo(peer)->Cheat_Spam_Delay = 3;
								pInfo(peer)->Cheat_FastPull = false;
								pInfo(peer)->Cheat_FastDrop = false;
								pInfo(peer)->Cheat_FastTrash = false;
								pInfo(peer)->Cheat_AutoCollect = false;
								pInfo(peer)->Cheat_FastSpin = false;
								pInfo(peer)->Cheat_Spam_Text = "`c" + server_name + " `wBest Server";
								update_clothes(peer);
							}
							else {
								try {
									pInfo(peer)->Cheat_HideOther = atoi(explode("\n", explode("checkbox_cheat_hideother|", cch)[1])[0].c_str()) == 1 ? true : false;
									if (pInfo(peer)->Cheat_HideOther) {
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != pInfo(peer)->world or pInfo(currentPeer)->netID == pInfo(peer)->netID) continue;
											Algorithm::avatar_remove(peer, pInfo(currentPeer)->netID);
										}
									}
									pInfo(peer)->Cheat_HideChat = atoi(explode("\n", explode("checkbox_cheat_hidechat|", cch)[1])[0].c_str()) == 1 ? true : false;
									pInfo(peer)->Cheat_AB = atoi(explode("\n", explode("checkbox_cheat_antibounce|", cch)[1])[0].c_str()) == 1 ? true : false;
									pInfo(peer)->Cheat_AF = atoi(explode("\n", explode("checkbox_cheat_autofarm|", cch)[1])[0].c_str()) == 1 ? true : false;
									pInfo(peer)->god_speed = atoi(explode("\n", explode("checkbox_cheat_speed|", cch)[1])[0].c_str()) == 1 ? true : false;
									pInfo(peer)->JumpCheat = atoi(explode("\n", explode("checkbox_cheat_jump|", cch)[1])[0].c_str()) == 1 ? true : false;
									pInfo(peer)->cheat_kick = atoi(explode("\n", explode("checkbox_cheat_kick|", cch)[1])[0].c_str()) == 1 ? true : false;
									pInfo(peer)->cheat_ban = atoi(explode("\n", explode("checkbox_cheat_ban|", cch)[1])[0].c_str()) == 1 ? true : false;
									pInfo(peer)->Cheat_AutoCollect = atoi(explode("\n", explode("checkbox_cheat_autocollect|", cch)[1])[0].c_str()) == 1 ? true : false;
									pInfo(peer)->Cheat_FastPull = atoi(explode("\n", explode("checkbox_cheat_fastpull|", cch)[1])[0].c_str()) == 1 ? true : false;
									pInfo(peer)->Cheat_FastDrop = atoi(explode("\n", explode("checkbox_cheat_fastdrop|", cch)[1])[0].c_str()) == 1 ? true : false;
									pInfo(peer)->Cheat_FastTrash = atoi(explode("\n", explode("checkbox_cheat_fasttrash|", cch)[1])[0].c_str()) == 1 ? true : false;
									pInfo(peer)->Cheat_FastSpin = atoi(explode("\n", explode("checkbox_cheat_fastspin|", cch)[1])[0].c_str()) == 1 ? true : false;
									if (not pInfo(peer)->Cheat_AF and pInfo(peer)->Cheat_AF_PunchX != 0 and pInfo(peer)->Cheat_AF_PunchY != 0 and pInfo(peer)->Cheat_AF_PlantingTree != 0) pInfo(peer)->Cheat_AF_PunchX = 0, pInfo(peer)->Cheat_AF_PunchY = 0, pInfo(peer)->Cheat_AF_PlantingTree = 0, pInfo(peer)->Cheat_AF_isRunning = false, pInfo(peer)->isFacingLeft = false;
									if (!is_number(explode("\n", explode("text_input_spam_delay|", cch)[1])[0])) break;
									if (atoi(explode("\n", explode("text_input_spam_delay|", cch)[1])[0].c_str()) < 1) break;
									pInfo(peer)->Cheat_Spam_Delay = atoi(explode("\n", explode("text_input_spam_delay|", cch)[1])[0].c_str());
									string text = explode("\n", explode("text_input_spam_chat|", cch)[1])[0];
									if (text.length() > 120) break;
									pInfo(peer)->Cheat_Spam_Text = text;
									pInfo(peer)->Cheat_Spam = atoi(explode("\n", explode("checkbox_cheat_spam|", cch)[1])[0].c_str()) == 1 ? true : false;
									update_clothes(peer);
								}
								catch (...) {
									break;
								}
							}
						}
						else if (cch.find("action|dialog_return\ndialog_name|ringmaster1\nbuttonClicked|requir") != string::npos) {
							int bgl = 0, ticket = 0, block = 0, door = 0;
							modify_inventory(peer, 7188, bgl);
							modify_inventory(peer, 1898, ticket);
							modify_inventory(peer, 1674, door);
							modify_inventory(peer, 262, block);
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							p.Insert("set_default_color|`o\nadd_label_with_icon|big|`9The Ringmaster|left|1900|\nadd_spacer|small|\nadd_textbox|`oYou must have all the Requirements below to get a gift item from me|\nadd_spacer|small|\nadd_textbox|`2Requirements List:|\nadd_spacer|small|\nadd_label_with_icon|small|`o(" + to_string(bgl) + "/1) Blue Gem Lock.|left|7188|\nadd_label_with_icon|small|`o(" + to_string(door) + "/1) `4Phoenix Wings.|left|1674|\nadd_label_with_icon|small|`o(" + to_string(block) + "/100) Crystal Blocks.|left|262|\nadd_label_with_icon|small|`o(" + to_string(ticket) + "/100) Golden Ticket.|left|1898|\nadd_label_with_icon|small|`o(" + setGems(pInfo(peer)->gems) + "/10.000) Gems.|left|9438|\nadd_spacer|small|\nend_dialog|goodbyee|`$GoodLuck!|");
							p.CreatePacket(peer);
							break;
						}
							else if (cch.find("action|dialog_return\ndialog_name|ringmaster1\nbuttonClicked|ring1") != string::npos) {
							vector<int> list2{ 1874, 1876, 1996, 2970, 3140, 3174, 1780, 1782, 1784, 6028, 6846, 8962, 11094, 1904, 1986, 1932 };
							int receive = 1, item = list2[rand() % list2.size()], got = 1;
							int remove = 0, bgl = 0, ticket = 0, block = 0, door = 0;
							modify_inventory(peer, 7188, bgl);
							modify_inventory(peer, 1898, ticket);
							modify_inventory(peer, 1674, door);
							modify_inventory(peer, 262, block);
							if (bgl < 1 || ticket < 100 || block < 100 || door < 1 || pInfo(peer)->gems < 10000) {
								gamepacket_t p;
								p.Insert("OnTextOverlay");
								p.Insert("Need more requirements.");
								p.CreatePacket(peer);
								continue;
							}
							if (bgl >= 1 || ticket >= 100 || block >= 100 || door >= 1 || pInfo(peer)->gems >= 10000) {
								if (get_free_slots(pInfo(peer)) >= 3) {
									modify_inventory(peer, 7188, remove = -1);
									modify_inventory(peer, 1898, remove = -100);
									modify_inventory(peer, 1674, remove = -1);
									modify_inventory(peer, 262, remove = -100);
									modify_inventory(peer, item, receive); // receiving 
									pInfo(peer)->gems -= 10000;
									gamepacket_t p, p2, p3;
									p.Insert("OnTextOverlay");
									p.Insert("Well Well well.. You got " + items[item].ori_name + "!");
									p3.Insert("OnSetBux");
									p3.Insert(pInfo(peer)->gems);
									p3.Insert(0);
									p3.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
									if (pInfo(peer)->supp >= 2) {
										p.Insert((float)33796, (float)1, (float)0);
									}
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										p2.Insert("OnParticleEffect");
										p2.Insert(90), p2.Insert((float)pInfo(peer)->x + 10, (float)pInfo(peer)->y + 16);
										if (pInfo(currentPeer)->world == pInfo(peer)->world) p.CreatePacket(peer), p3.CreatePacket(peer), p2.CreatePacket(currentPeer);
										packet_(currentPeer, "action|log\nmsg|`5**Message from [`9The Ringmaster`5] in [`9" + pInfo(peer)->world + "`5]:** [`w" + pInfo(peer)->tankIDName + "`5] `5receive [`2" + items[item].ori_name + "`5]");
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnTextOverlay");
									p.Insert("You need at least 2 Free Space");
									p.Insert(0), p.Insert(1);
									p.CreatePacket(peer);
								}
							}
							break;
						}
							else if (cch.find("action|dialog_return\ndialog_name|account_security\nchange|") != string::npos) {
								string change = cch.substr(57, cch.length() - 57).c_str();
								replace_str(change, "\n", "");
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								if (change == "email") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|Having an up-to-date email address attached to your account is a great step toward improved account security.|left|\nadd_smalltext|Email: `5" + pInfo(peer)->email + "``|left|\nadd_spacer|small|\nadd_smalltext|Type your new `5email address``|left|\nadd_text_input|change|||50|\nend_dialog|change_email|OK|Continue|\n");
								else if (change == "password") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|A hacker may attempt to access your account more than once over a period of time.|left|\nadd_smalltext|Changing your password `2often reduces the risk that they will have frequent access``.|left|\nadd_spacer|small|\nadd_smalltext|Type your new `5password``|left|\nadd_text_input|change|||18|\nend_dialog|change_password|OK|Continue|\n");
								if (change == "email" or change == "password") p.CreatePacket(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|change_email\nchange|") != string::npos) {
								string change = cch.substr(53, cch.length() - 53).c_str();
								replace_str(change, "\n", "");
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								if (change == "") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|Having an up-to-date email address attached to your account is a great step toward improved account security.|left|\nadd_smalltext|Email: `5" + pInfo(peer)->email + "``|left|\nadd_spacer|small|\nadd_smalltext|Type your new `5email address``|left|\nadd_text_input|change|||50|\nend_dialog|change_email|OK|Continue|\n");
								else {
									pInfo(peer)->email = change;
									save_player(pInfo(peer), false);
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|Having an up-to-date email address attached to your account is a great step toward improved account security.|left|\nadd_smalltext|Your new Email: `5" + pInfo(peer)->email + "``|left|\nadd_spacer|small|\nend_dialog|changedemail|OK||\n");
								}
								p.CreatePacket(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|change_password\nchange|") != string::npos) {
								string change = cch.substr(56, cch.length() - 56).c_str();
								replace_str(change, "\n", "");
								gamepacket_t p;
								p.Insert("OnDialogRequest");
								if (change == "") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|A hacker may attempt to access your account more than once over a period of time.|left|\nadd_smalltext|Changing your password `2often reduces the risk that they will have frequent access``.|left|\nadd_spacer|small|\nadd_smalltext|Type your new `5password``|left|\nadd_text_input|change|||18|\nend_dialog|change_password|OK|Continue|\n");
								else {
									{
										gamepacket_t p;
										p.Insert("SetHasGrowID"), p.Insert(1), p.Insert(pInfo(peer)->tankIDName), p.Insert(pInfo(peer)->tankIDPass = change);
										p.CreatePacket(peer);
									}
									save_player(pInfo(peer), false);
									p.Insert("set_default_color|`o\nadd_label_with_icon|big|`0Account Security``|left|1424|\nadd_spacer|small|\nadd_textbox|`6Information``|left|\nadd_smalltext|A hacker may attempt to access your account more than once over a period of time.|left|\nadd_smalltext|Changing your password `2often reduces the risk that they will have frequent access``.|left|\nadd_smalltext|Your new password: `5" + pInfo(peer)->tankIDPass + "``|left|\nadd_spacer|small|\nend_dialog|changedpassword|OK||\n");
								}
								p.CreatePacket(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|world_swap\nname_box|") != string::npos) {
								string world = cch.substr(53, cch.length() - 53).c_str(), currentworld = pInfo(peer)->world;
								int got = 0;
								replace_str(world, "\n", "");
								transform(world.begin(), world.end(), world.begin(), ::toupper);
								if (not check_blast(world) || currentworld == world) {
									gamepacket_t p;
									p.Insert("OnDialogRequest"), p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSwap World Names``|left|2580|\nadd_textbox|`4World swap failed - you don't own both worlds!``|left|\nadd_smalltext|This will swap the name of the world you are standing in with another world `4permanently``.  You must own both worlds, with a World Lock in place.<CR>Your `wChange of Address`` will be consumed if you press `5Swap 'Em``.|left|\nadd_textbox|Enter the other world's name:|left|\nadd_text_input|name_box|||32|\nadd_spacer|small|\nend_dialog|world_swap|Cancel|Swap 'Em!|"), p.CreatePacket(peer);
								}
								else create_address_world(peer, world, currentworld);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|detects_1_1") != string::npos) {

							bool nocip_1 = atoi(explode("\n", explode("nocip_1_1|", cch)[1])[0].c_str());
							bool nocip_2 = atoi(explode("\n", explode("nocip_1_2|", cch)[1])[0].c_str());

							if (nocip_1) pInfo(peer)->cheat_detect = 1;
							else pInfo(peer)->cheat_detect = 0;

							if (nocip_2) pInfo(peer)->cheat_unacc = 1;
							else pInfo(peer)->cheat_unacc = 0;

							update_clothes(peer);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|modes_1_1") != string::npos) {

							bool nocip_1 = atoi(explode("\n", explode("nocip_1_1|", cch)[1])[0].c_str());
							bool nocip_2 = atoi(explode("\n", explode("nocip_1_2|", cch)[1])[0].c_str());

							//Auto Farm
							if (nocip_1) pInfo(peer)->cheat_qq = 1;
							else pInfo(peer)->cheat_qq = 0;

							if (nocip_2) pInfo(peer)->cheat_reme = 1;
							else pInfo(peer)->cheat_reme = 0;
							update_clothes(peer);
							break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|wrenchs_1_1") != string::npos) {

							bool nocip_1 = atoi(explode("\n", explode("nocip_1_1|", cch)[1])[0].c_str());
							bool nocip_2 = atoi(explode("\n", explode("nocip_1_2|", cch)[1])[0].c_str());
							bool nocip_3 = atoi(explode("\n", explode("nocip_1_3|", cch)[1])[0].c_str());

							if (nocip_1) pInfo(peer)->cheat_pull = 1;
							else pInfo(peer)->cheat_pull = 0;

							if (nocip_2) pInfo(peer)->cheat_kick = 1;
							else pInfo(peer)->cheat_kick = 0;

							if (nocip_3) pInfo(peer)->cheat_ban = 1;
							else pInfo(peer)->cheat_ban = 0;

							update_clothes(peer);
							break;
						}
							else if (cch.find("action|dialog_return\ndialog_name|surgery\nbuttonClicked|tool") != string::npos) {
							if (pInfo(peer)->surgery_started) {
								int count = atoi(cch.substr(59, cch.length() - 59).c_str());
								if (count == 999) end_surgery(peer);
								else load_surgery(peer, count);
							}
							break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|levelup\nbuttonClicked|claimreward") != string::npos) {
								int count = atoi(cch.substr(66, cch.length() - 66).c_str());
								if (count < 1 || count >125) break;
								if (std::find(pInfo(peer)->lvl_p.begin(), pInfo(peer)->lvl_p.end(), count) == pInfo(peer)->lvl_p.end()) {
									if (pInfo(peer)->level >= count) {
										pInfo(peer)->lvl_p.push_back(count);
										packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
										gamepacket_t p;
										p.Insert("OnSetBux");
										p.Insert(pInfo(peer)->kit += count * 10);
										p.Insert(0);
										p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
										if (pInfo(peer)->supp >= 2) {
											p.Insert((float)33796, (float)1, (float)0);
										}
										p.CreatePacket(peer);
										{
											gamepacket_t p;
											p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("Congratulations! You have received your Level Up Reward!"), p.Insert(0), p.Insert(0), p.CreatePacket(peer);
										}
										PlayerMoving data_{};
										data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
										BYTE* raw = packPlayerMoving(&data_);
										send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										delete[] raw;
										level_show(peer);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|statsblock\nisStatsWorldBlockUsableByPublic") != string::npos) {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								bool world_public = atoi(explode("\n", t_[3])[0].c_str()), floating_public = atoi(explode("\n", t_[4])[0].c_str()),  changed = false;
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									if (pInfo(peer)->tankIDName == world_->owner_name) {
										for (int i_ = 0; i_ < world_->gscan.size(); i_++) {
											if (world_->gscan[i_].x == pInfo(peer)->lastwrenchx and world_->gscan[i_].y == pInfo(peer)->lastwrenchy) {
											changed = true;
											world_->gscan[i_].world_public = world_public;
											 world_->gscan[i_].floating_public = floating_public;
											}
										}
									}
									if (changed == false) {
										WorldGrowscan gscan_{};
										gscan_.x = pInfo(peer)->lastwrenchx, gscan_.y = pInfo(peer)->lastwrenchy;
										gscan_.world_public = world_public, gscan_.floating_public = floating_public;
										world_->gscan.push_back(gscan_);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|statsblock\nbuttonClicked|back_to_gscan\n") != string::npos || cch.find("action|dialog_return\ndialog_name|statsblockworld\nbuttonClicked|back_to_gscan\n") != string::npos) {
								edit_tile(peer, pInfo(peer)->lastwrenchx, pInfo(peer)->lastwrenchy, 32);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|statsblock\nbuttonClicked|floatingItems\n") != string::npos) {
								send_growscan_floating(peer, "start", "1");
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|statsblock\nbuttonClicked|serilrffd232eeeeadafdfltiifgdIfsfslLgsfs24") != string::npos) {
								try {
									string type = cch.substr(65, 1);
									string search = cch.substr(79, cch.length() - 79);
									if (type.empty()) break;
									if (search.empty()) break;
									replace_str(search, "\n", "");
									replace_str(type, "\n", "");
									send_growscan_floating(peer, search, type);
								}
								catch (out_of_range) {
									break;
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|statsblock\nbuttonClicked|worldBlocks\n") != string::npos || cch.find("action|dialog_return\ndialog_name|statsblockworld\nbuttonClicked|worldBlocks\n") != string::npos) {
							if (cch.find("action|dialog_return\ndialog_name|statsblock\nbuttonClicked|worldBlocks\n") != string::npos) send_growscan_worldblocks(peer, "start", "1");
							if (cch.find("action|dialog_return\ndialog_name|statsblockworld\nbuttonClicked|worldBlocks\n") != string::npos) send_growscan_worldblocks(peer, "start", "1");
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|statsblockworld\nbuttonClicked|serilrffd232eeeeadafdfltiifgdIfsfslLgsfs24") != string::npos) {
								try {
									if (cch.length() < 84) break;
									string type = cch.substr(70, 1);
									if (type.empty()) break;
									string search = cch.substr(84, cch.length() - 84);
									if (search.empty()) break;
									replace_str(search, "\n", "");
									replace_str(type, "\n", "");
									send_growscan_worldblocks(peer, search, type);
								}
								catch (exception) { break; }
								break;
								}
							if (cch.find("action|dialog_return\ndialog_name|billboard_edit\nbillboard_toggle|") != string::npos) {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								int billboard_active = atoi(explode("\n", t_[3])[0].c_str());
								int billboard_price = atoi(explode("\n", t_[4])[0].c_str());
								int peritem = atoi(explode("\n", t_[5])[0].c_str());
								int perlock = atoi(explode("\n", t_[6])[0].c_str());
								bool update_billboard = true;
								if (peritem == perlock or peritem == 0 and perlock == 0 or peritem == 1 and perlock == 1) {
									update_billboard = false;
									gamepacket_t p, p2;
									p.Insert("OnConsoleMessage"), p.Insert("You need to pick one pricing method - 'locks per item' or 'items per lock'"), p.CreatePacket(peer);
									p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("You need to pick one pricing method - 'locks per item' or 'items per lock'"), p2.Insert(0), p2.Insert(1), p2.CreatePacket(peer);
								}
								else {
									if (peritem == 1) pInfo(peer)->b_w = 1;
									if (perlock == 1) pInfo(peer)->b_w = 0;
								}
								if (billboard_active == 1)pInfo(peer)->b_a = 1;
								else pInfo(peer)->b_a = 0;
								if (billboard_price < 0 or billboard_price > 99999) {
									update_billboard = false;
									gamepacket_t p, p2;
									p.Insert("OnConsoleMessage"), p.Insert("Price can't be negative. That's beyond science."), p.CreatePacket(peer);
									p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("Price can't be negative. That's beyond science."), p2.Insert(0), p2.Insert(1), p2.CreatePacket(peer);
								}//gabut nunggu build
								else pInfo(peer)->b_p = billboard_price;
								if (update_billboard && pInfo(peer)->b_p != 0 && pInfo(peer)->b_i != 0) {
									gamepacket_t p(0, pInfo(peer)->netID);
									p.Insert("OnBillboardChange"), p.Insert(pInfo(peer)->netID), p.Insert(pInfo(peer)->b_i), p.Insert(pInfo(peer)->b_a), p.Insert(pInfo(peer)->b_p), p.Insert(pInfo(peer)->b_w);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != pInfo(peer)->world) continue;
										p.CreatePacket(currentPeer);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|dialog_scarf_of_seasons\nbuttonClicked") != string::npos) {
								if (pInfo(peer)->necklace == 11818) pInfo(peer)->i_11818_1 = 0, pInfo(peer)->i_11818_2 = 0, update_clothes(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|title_edit\nbuttonClicked|") != string::npos) {
								if (pInfo(peer)->drtitle) pInfo(peer)->drt = atoi(explode("\n", explode("checkbox_doctor_title|", cch)[1])[0].c_str());
								if (pInfo(peer)->level >= 125) pInfo(peer)->bxoost = atoi(explode("\n", explode("checkbox_bxoost_title|", cch)[1])[0].c_str());
								if (pInfo(peer)->level >= 125) pInfo(peer)->lvl125 = atoi(explode("\n", explode("checkbox_maxlevel_title|", cch)[1])[0].c_str());
								if (pInfo(peer)->legend) pInfo(peer)->is_legend = atoi(explode("\n", explode("checkbox_legend_title|", cch)[1])[0].c_str());
								if (pInfo(peer)->have_master || pInfo(peer)->gp) pInfo(peer)->master = atoi(explode("\n", explode("checkbox_master_title|", cch)[1])[0].c_str());
								if (pInfo(peer)->have_donor || pInfo(peer)->gp) pInfo(peer)->donor = atoi(explode("\n", explode("checkbox_g4g_title|", cch)[1])[0].c_str());
								update_clothes(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|bulletin_edit\nsign_text|\ncheckbox_locked|") != string::npos) {
								try {
									vector<string> t_ = explode("|", cch);
									if (t_.size() < 4) break;
									bool public_can_add = atoi(explode("\n", t_.at(4)).at(0).c_str()),  hide_names = atoi(explode("\n", t_.at(5)).at(0).c_str());
									bool changed = false;
									string name_ = pInfo(peer)->world;
									vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									if (p != worlds.end()) {
										World* world_ = &worlds[p - worlds.begin()];
										if (pInfo(peer)->tankIDName == world_->owner_name) {
											for (int i_ = 0; i_ < world_->bulletins.size(); i_++) {
												if (world_->bulletins.at(i_).x == pInfo(peer)->lastwrenchx and world_->bulletins.at(i_).y == pInfo(peer)->lastwrenchy) {
													changed = true;
													world_->bulletins.at(i_).public_can_add = public_can_add;
													world_->bulletins.at(i_).hide_names = hide_names;
												}
											}
										}
										if (changed == false) {
											WorldBulletinSettings set_{};
											set_.x = pInfo(peer)->lastwrenchx, set_.y = pInfo(peer)->lastwrenchy, set_.public_can_add = public_can_add, set_.hide_names = hide_names;
											world_->bulletins.push_back(set_);
										}
									}
								}
								catch (out_of_range) {
									break;
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|camera_edit\ncheckbox_showpick|") != string::npos) {
								try {
									vector<string> t_ = explode("|", cch);
									if (t_.size() < 4) break;
									bool show_item_taking = atoi(explode("\n", t_.at(3)).at(0).c_str()), show_item_dropping = atoi(explode("\n", t_.at(4)).at(0).c_str()),  show_people_entering = atoi(explode("\n", t_.at(5)).at(0).c_str()), show_people_exiting = atoi(explode("\n", t_.at(6)).at(0).c_str()), dont_show_owner = atoi(explode("\n", t_.at(7)).at(0).c_str()), dont_show_admins = atoi(explode("\n", t_.at(8)).at(0).c_str()),  dont_show_noaccess = atoi(explode("\n", t_.at(9)).at(0).c_str()), changed = false;
									string name_ = pInfo(peer)->world;
									vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									if (p != worlds.end()) {
										World* world_ = &worlds[p - worlds.begin()];
										for (int i_ = 0; i_ < world_->cctv_settings.size(); i_++) {
											if (world_->cctv_settings.at(i_).x == pInfo(peer)->lastwrenchx and world_->cctv_settings.at(i_).y == pInfo(peer)->lastwrenchy) {
												changed = true;
												world_->cctv_settings.at(i_).show_item_taking = show_item_taking;
												world_->cctv_settings.at(i_).show_item_dropping = show_item_dropping;
												world_->cctv_settings.at(i_).show_people_entering = show_people_entering;
												world_->cctv_settings.at(i_).show_people_exiting = show_people_exiting;
												world_->cctv_settings.at(i_).dont_show_owner = dont_show_owner;
												world_->cctv_settings.at(i_).dont_show_admins = dont_show_admins;
												world_->cctv_settings.at(i_).dont_show_noaccess = dont_show_noaccess;
											}
										}
										if (changed == false) {
											WorldCCTVSettings cctvs_{};
											cctvs_.x = pInfo(peer)->lastwrenchx, cctvs_.y = pInfo(peer)->lastwrenchy;
											cctvs_.show_item_taking = show_item_taking, cctvs_.show_item_dropping = show_item_dropping, cctvs_.show_people_entering = show_people_entering, cctvs_.show_people_exiting = show_people_exiting, cctvs_.dont_show_owner = dont_show_owner, cctvs_.dont_show_admins = dont_show_admins, cctvs_.dont_show_noaccess = dont_show_noaccess;
											world_->cctv_settings.push_back(cctvs_);
										}
									}
								}
								catch (out_of_range) {
									break;
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|camera_edit\nbuttonClicked|clear") != string::npos) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									for (int i_ = 0; i_ < world_->cctv.size(); i_++)if (world_->cctv[i_].x == pInfo(peer)->lastwrenchx and world_->cctv[i_].y == pInfo(peer)->lastwrenchy) {
										if (i_ != 0) {
											world_->cctv.erase(world_->cctv.begin() + i_);
											i_--;
										}
									}
								}
								{
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("`2Camera log cleared.``"), p.Insert(0), p.Insert(0), p.CreatePacket(peer);
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|b_claimreward") != string::npos) {
								int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
								vector<int> list{ 6896, 6948, 1068, 1966, 1836, 5080, 10754, 1874, 6946 };
								if (reward <= 0 || reward > list.size()) break;
								if (list[reward - 1] == 1068) count = 10;
								if (find(pInfo(peer)->bb_p.begin(), pInfo(peer)->bb_p.end(), lvl = reward * 5) == pInfo(peer)->bb_p.end()) {
									if (pInfo(peer)->bb_lvl >= lvl) {
										if (modify_inventory(peer, list[reward - 1], count) == 0) {
											pInfo(peer)->bb_p.push_back(lvl);
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											{
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("Congratulations! You have received your Builder Reward!");
												p.Insert(0), p.Insert(0);
												p.CreatePacket(peer);
											}
											PlayerMoving data_{};
											data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
											BYTE* raw = packPlayerMoving(&data_);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw;
											{
												PlayerMoving data_{};
												data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
												int32_t to_netid = pInfo(peer)->netID;
												BYTE* raw = packPlayerMoving(&data_);
												raw[3] = 5;
												memcpy(raw + 8, &to_netid, 4);
												send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												delete[] raw;
											}
											builder_reward_show(peer);
										}
										else {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("You have full inventory space!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|autoclave\nbuttonClicked|tool") != string::npos) {
								int itemtool = atoi(cch.substr(61, cch.length() - 61).c_str());
								if (itemtool == 1258 || itemtool == 1260 || itemtool == 1262 || itemtool == 1264 || itemtool == 1266 || itemtool == 1268 || itemtool == 1270 || itemtool == 4308 || itemtool == 4310 || itemtool == 4312 || itemtool == 4314 || itemtool == 4316 || itemtool == 4318) {
									int got = 0;
									modify_inventory(peer, itemtool, got);
									if (got >= 20) {
										pInfo(peer)->lastchoosenitem = itemtool;
										gamepacket_t p;
										p.Insert("OnDialogRequest");
										p.Insert("set_default_color|`o\nadd_label_with_icon|big|`9Autoclave``|left|4322|\nadd_spacer|small|\nadd_textbox|Are you sure you want to destroy 20 " + items[itemtool].ori_name + " in exchange for one of each of the other 12 surgical tools?|left|\nadd_button|verify|Yes!|noflags|0|0|\nend_dialog|autoclave|Cancel||");
										p.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|autoclave\nbuttonClicked|verify") != string::npos) {
								int removeitem = pInfo(peer)->lastchoosenitem, inventory_space = 12, slots = get_free_slots(pInfo(peer)), got = 0;
								modify_inventory(peer, removeitem, got);
								if (got >= 20) {
									vector<int> noobitems{ 1262, 1266, 1264, 4314, 4312, 4318, 4308, 1268, 1258, 1270, 4310, 4316 };
									bool toobig = false;
									for (int i_ = 0, remove = 0; i_ < pInfo(peer)->inv.size(); i_++) for (int i = 0; i < noobitems.size(); i++) {
										if (pInfo(peer)->inv[i_].id == noobitems[i]) {
											if (pInfo(peer)->inv[i_].count == 200) toobig = true;
											else inventory_space -= 1;
										}
									}
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
									if (toobig == false && slots >= inventory_space) {
										modify_inventory(peer, removeitem, got = -20);
										for (int i = 0; i < noobitems.size(); i++) {
											if (noobitems[i] == removeitem) continue;
											modify_inventory(peer, noobitems[i], got = 1);
										}
										gamepacket_t p2;
										p.Insert("[`3I swapped 20 " + items[removeitem].ori_name + " for 1 of every other instrument!``]");
										p2.Insert("OnTalkBubble"), p2.Insert("[`3I swapped 20 " + items[removeitem].name + " for 1 of every other instrument!``]"), p2.CreatePacket(peer);
									}
									else p.Insert("No inventory space!");
									p.Insert(0), p.Insert(1), p.CreatePacket(peer);
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|extractor\nbuttonClicked|extractOnceObj_") != string::npos) {
								int got = 0;
								modify_inventory(peer, 6140, got);
								if (got >= 1) {
									string name_ = pInfo(peer)->world;
									vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									if (p != worlds.end()) {
										World* world_ = &worlds[p - worlds.begin()];
										int uid = atoi(cch.substr(72, cch.length() - 72).c_str());
										if (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and (!guild_access(peer, world_->guild_id) and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end())) break;
										for (int i_ = 0; i_ < world_->drop.size(); i_++) {
											if (world_->drop[i_].id != 0 && world_->drop[i_].x > 0 && world_->drop[i_].y > 0 && world_->drop[i_].uid == uid) {
												gamepacket_t p;
												p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
												int c_ = world_->drop[i_].count;
												if (modify_inventory(peer, world_->drop[i_].id, c_) == 0) {
													modify_inventory(peer, 6140, got = -1);
													p.Insert("You have extracted " + to_string(world_->drop[i_].count) + " " + items[world_->drop[i_].id].name + ".");
													int32_t to_netid = pInfo(peer)->netID;
													PlayerMoving data_{}, data2_{};
													data_.effect_flags_check = 1, data_.packetType = 14, data_.netID = 0, data_.plantingTree = world_->drop[i_].uid;
													data2_.x = world_->drop[i_].x, data2_.y = world_->drop[i_].y, data2_.packetType = 19, data2_.plantingTree = 500, data2_.punchX = world_->drop[i_].id, data2_.punchY = pInfo(peer)->netID;
													BYTE* raw = packPlayerMoving(&data_);
													BYTE* raw2 = packPlayerMoving(&data2_);
													raw2[3] = 5;
													memcpy(raw2 + 8, &to_netid, 4);
													for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
														if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != name_) continue;
														send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
														send_raw(currentPeer, 4, raw2, 56, ENET_PACKET_FLAG_RELIABLE);
													}
													delete[]raw, raw2;
													world_->drop[i_].id = 0, world_->drop[i_].x = -1, world_->drop[i_].y = -1;
												}
												else p.Insert("No inventory space.");
												p.CreatePacket(peer);
											}
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|zombie_back\nbuttonClicked|zomb_price_") != string::npos) {
							int item = atoi(cch.substr(70, cch.length() - 70).c_str());
							if (item <= 0 || item >= items.size() || items[item].zombieprice == 0) continue;
							pInfo(peer)->lockeitem = item;
							int zombie_brain = 0, pile = 0, total = 0;
							modify_inventory(peer, 4450, zombie_brain);
							modify_inventory(peer, 4452, pile);
							total += zombie_brain + (pile * 100);
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							if (total >= items[item].zombieprice) p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSales-Man``|left|4358|\nadd_textbox|" + items[item].name + " costs " + setGems(items[item].zombieprice) + " Zombie Brains. Are you sure you want to buy it? You have " + setGems(total) + " Zombie Brains.|left|\nadd_button|zomb_item_|Yes, please|noflags|0|0|\nadd_button|back|No, thanks|noflags|0|0|\nend_dialog|zombie_purchase|Hang Up||\n");
							else p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSales-Man``|left|4358|\nadd_textbox|" + items[item].name + " costs " + setGems(items[item].zombieprice) + " Zombie Brains. You only have " + setGems(total) + " Zombie Brains so you can't afford it. Sorry!|left|\nadd_button|chc3_1|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
							p.CreatePacket(peer);
							break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|zurgery_back\nbuttonClicked|zurg_price_") != string::npos) {
							int item = atoi(cch.substr(71, cch.length() - 71).c_str());
							if (item <= 0 || item >= items.size() || items[item].surgeryprice == 0) continue;
							pInfo(peer)->lockeitem = item;
							int zombie_brain = 0, pile = 0, total = 0;
							modify_inventory(peer, 4298, zombie_brain);
							modify_inventory(peer, 4300, pile);
							total += zombie_brain + (pile * 100);
							gamepacket_t p;
							p.Insert("OnDialogRequest");
							if (total >= items[item].surgeryprice) p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSales-Man``|left|4358|\nadd_textbox|" + items[item].name + " costs " + setGems(items[item].surgeryprice) + " Caduceus. Are you sure you want to buy it? You have " + setGems(total) + " Caduceus.|left|\nadd_button|zurg_item_|Yes, please|noflags|0|0|\nadd_button|back|No, thanks|noflags|0|0|\nend_dialog|zurgery_purchase|Hang Up||\n");
							else p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wSales-Man``|left|4358|\nadd_textbox|" + items[item].name + " costs " + setGems(items[item].surgeryprice) + " Caduceus. You only have " + setGems(total) + " Caduceus so you can't afford it. Sorry!|left|\nadd_button|chc4_1|Back|noflags|0|0|\nend_dialog|3898|Hang Up||\n");
							p.CreatePacket(peer);
							break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|giantpotogold\namt|") != string::npos) {
								int count = atoi(cch.substr(51, cch.length() - 51).c_str()), got = 0;
								modify_inventory(peer, pInfo(peer)->lastchoosenitem, got);
								if (got <= 0 || count <= 0 || count > items.size()) break;
								int item = pInfo(peer)->lastchoosenitem;
								if (items[item].untradeable == 1 || item == 1424 || items[item].rarity >= 363 || items[item].rarity == 0 || items[item].rarity < 1 || count > got) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									if (count > got) p.Insert("You don't have that to give!");
									else p.Insert("I'm sorry, we can't accept items without rarity!");
									p.CreatePacket(peer);
								}
								else {
									pInfo(peer)->b_ra += count * items[item].rarity;
									modify_inventory(peer, pInfo(peer)->lastchoosenitem, count *= -1);
									if (pInfo(peer)->b_ra >= 20000) pInfo(peer)->b_lvl = 2;
									int chance = 29;
									if (pInfo(peer)->b_ra > 25000) chance += 7;
									if (pInfo(peer)->b_ra > 40000) chance += 25;
									if (rand() % 100 < chance && pInfo(peer)->b_ra >= 20000) {
										int give_count = 1, given_count = 1;
										vector<int> list{ 7978,5734, 7986,5724,7980,7990,5730,5726,5728,7988,7992 };
										if (pInfo(peer)->b_ra >= 40000 && rand() % 100 < 15) list = { 7978,5734, 7986,5724,7980,7990,5730,5726,5728,7988,7992, 7996,5718,5720,9418,5732,5722,8000,5740,8002,9414,11728,11730 };
										int given_item = list[rand() % list.size()];
										if (given_item == 7978 || given_item == 5734 || given_item == 7986 || given_item == 5724 || given_item == 7992 || given_item == 7980 || given_item == 7990) give_count = 5, given_count = 5;
										if (given_item == 5730 || given_item == 5726 || given_item == 5728 || given_item == 7988 || given_item == 7980 || given_item == 7990) give_count = 10, given_count = 10;
										if (modify_inventory(peer, given_item, given_count) == 0) {
											gamepacket_t p, p2;
											p.Insert("OnConsoleMessage"), p.Insert(a + "Thanks for your generosity! The pot overflows with `6" + (pInfo(peer)->b_ra < 40000 ? "20" : "40") + ",000 rarity``! Your `6Level 2 prize`` is a fabulous `2" + items[given_item].name + "!``"), p.CreatePacket(peer);
											p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert(a + "Thanks for your generosity! The pot overflows with `6" + (pInfo(peer)->b_ra < 40000 ? "20" : "40") + ",000 rarity``! Your `6Level 2 prize`` is a fabulous `2" + items[given_item].name + "!``"), p2.CreatePacket(peer);
											pInfo(peer)->b_lvl = 1, pInfo(peer)->b_ra = 0;
										}
										else {
											gamepacket_t p;
											p.Insert("OnConsoleMessage"), p.Insert("No inventory space."), p.CreatePacket(peer);
										}
									}
									else {
										gamepacket_t p;
										p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("Thank you for your generosity!"), p.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|donation_box_edit\nbuttonClicked|clear_selected\n") != string::npos) {
								try {
									bool took = false, fullinv = false;
									gamepacket_t p3;
									p3.Insert("OnTalkBubble"), p3.Insert(pInfo(peer)->netID);
									string name_ = pInfo(peer)->world;
									vector<string> t_ = explode("|", cch);
									if (t_.size() < 4) break;
									vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
									if (p != worlds.end()) {
										World* world_ = &worlds[p - worlds.begin()];
										if (world_->owner_name != pInfo(peer)->tankIDName and not pInfo(peer)->dev and not world_->owner_name.empty() and (!guild_access(peer, world_->guild_id) and find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) == world_->admins.end())) break;
										WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
										if (!items[block_->fg].donation) break;
										for (int i_ = 0, remove_ = 0; i_ < block_->donates.size(); i_++, remove_++) {
											if (atoi(explode("\n", t_.at(4 + remove_)).at(0).c_str())) {
												int receive = block_->donates[i_].count;
												if (modify_inventory(peer, block_->donates[i_].item, block_->donates[i_].count) == 0) {
													took = true;
													for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
														if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->ispatrol == false) continue;
														gamepacket_t p;
														p.Insert("OnConsoleMessage");
														p.Insert("`9[PATROL] `0" + pInfo(peer)->tankIDName + " `oreceive `0" + items[block_->donates[i_].item].name + " `o" + to_string(receive) + "x from `0" + block_->donates[i_].name + "`oin `9" + pInfo(peer)->world + "`o.");
														p.CreatePacket(currentPeer);
													}
													gamepacket_t p;
													p.Insert("OnConsoleMessage"), p.Insert("`7[``" + pInfo(peer)->tankIDName + " receives `5" + to_string(receive) + "`` `w" + items[block_->donates[i_].item].name + "`` from `w" + block_->donates[i_].name + "``, how nice!`7]``");
													block_->donates.erase(block_->donates.begin() + i_), i_--;
													for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
														if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(peer)->world != pInfo(currentPeer)->world) continue;
														p.CreatePacket(currentPeer);
													}
												}
												else fullinv = true;
											}
										}
										if (block_->donates.size() == 0) {
											WorldBlock block_ = world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
											PlayerMoving data_{};
											data_.packetType = 5, data_.punchX = pInfo(peer)->lastwrenchx, data_.punchY = pInfo(peer)->lastwrenchy, data_.characterState = 0x8;
											BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, &block_));
											BYTE* blc = raw + 56;
											form_visual(blc, block_, *world_, peer, false);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												send_raw(currentPeer, 4, raw, 112 + alloc_(world_, &block_), ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw, blc;
										}
									}
									if (fullinv) {
										p3.Insert("I don't have enough room in my backpack to get the item(s) from the box!");
										gamepacket_t p2;
										p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("`2(Couldn't get all of the gifts)``"), p2.CreatePacket(peer);
									}
									else if (took) p3.Insert("`2Box emptied.``");
									p3.CreatePacket(peer);
								}
								catch (out_of_range) {
									break;
								}
							break;
							}
							else if (cch == "action|claimdailyreward\n") {
								if (pInfo(peer)->pinata_prize == false) {
									int c_ = 1;
									gamepacket_t p_c;
									p_c.Insert("OnConsoleMessage");
									if (modify_inventory(peer, 9616, c_) == 0) {
										pInfo(peer)->pinata_day = today_day;
										pInfo(peer)->pinata_prize = true;
										pInfo(peer)->pinata_claimed = false;
										gamepacket_t p, p2;
										p.Insert("OnProgressUIUpdateValue"), p.Insert(pInfo(peer)->pinata_claimed ? 1 : 0), p.Insert(pInfo(peer)->pinata_prize ? 1 : 0), p.CreatePacket(peer);
										p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("You got a Block De Mayo Block!"), p2.CreatePacket(peer);
										p_c.Insert("You got a Block De Mayo Block!");
									}
									else  p_c.Insert("You got a Block De Mayo Block!"),
										p_c.CreatePacket(peer);
								}
								break;
							}
							else if (cch == "action|showcincovolcaniccape\n" || cch == "action|showcincovolcanicwings\n") {
							gamepacket_t p(500);
							p.Insert("OnDialogRequest");
							if (cch == "action|showcincovolcanicwings\n") p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wVolcanic Ventures : Volcanic Wings``|left|11870|\nadd_spacer|small|\nadd_textbox|Every `224 hours``, a limited amount of `2Volcanic Wings`` will be released into the game!|left|\nadd_spacer|small|\nadd_textbox|For your chance to find one of these `#Rare`` items, smash a `2Lava Pinata``. |left|\nadd_spacer|small|\nadd_textbox|There will only be 48 released every 24 hours so, be quick!|left|\nadd_spacer|small|\nadd_textbox|Did you know there are 48 active Volcanoes in Mexico?|left|\nend_dialog|volcanic_quest||OK|");
							else p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wVolcanic Ventures : Volcanic Cape``|left|10806|\nadd_spacer|small|\nadd_textbox|Every `224 hours``, a limited amount of `2Volcanic Cape`` will be released into the game!|left|\nadd_spacer|small|\nadd_textbox|For your chance to find one of these `#Rare`` items, smash a `2Lava Pinata``. |left|\nadd_spacer|small|\nadd_textbox|There will only be 48 released every 24 hours so, be quick!|left|\nadd_spacer|small|\nadd_textbox|Did you know there are 48 active Volcanoes in Mexico?|left|\nend_dialog|volcanic_quest||OK|");
							p.CreatePacket(peer);
							break;
							}
							else if (cch == "action|dailyrewardmenu\n") {
							gamepacket_t p(500);
							p.Insert("OnDailyRewardRequest");
							if (pInfo(peer)->pinata_prize) {
								struct tm newtime;
								time_t now = time(0);
								localtime_s(&newtime, &now);
								p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wBlock De Mayo|left|9616|\nset_default_color|`o\nadd_image_button||interface/large/gui_shop_buybanner.rttex|bannerlayout|flag_frames:4,1,3,0|flag_surfsize:512,200|\nadd_smalltext|`7Get involved and get rewards!`` Smash an Ultra Pinata once a day during `5Cinco de Mayo Week`` and get a daily reward!|left|\nadd_spacer|small|\nadd_button|claimbutton|Come Back Later|noflags|0|0|\nadd_countdown|" + to_string(24 - newtime.tm_hour) + "H" + (60 - newtime.tm_min != 0 ? " " + to_string(60 - newtime.tm_min) + "M" : "") + "|center|disable|\nadd_quick_exit|");
							}
							else {
								if (pInfo(peer)->pinata_claimed) p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wBlock De Mayo|left|9616|\nset_default_color|`o\nadd_image_button||interface/large/gui_shop_buybanner.rttex|bannerlayout|flag_frames:4,1,3,0|flag_surfsize:512,200|\nadd_smalltext|`7Get involved and get rewards!`` Smash an Ultra Pinata once a day during `5Cinco de Mayo Week`` and get a daily reward!|left|\nadd_spacer|small|\nadd_button|claimbutton|CLAIM|noflags|0|0|\nadd_countdown||center|enable|\nadd_quick_exit|");
								else p.Insert("set_default_color|`o\nadd_label_with_icon|big|`wBlock De Mayo|left|9616|\nset_default_color|`o\nadd_image_button||interface/large/gui_shop_buybanner.rttex|bannerlayout|flag_frames:4,1,3,0|flag_surfsize:512,200|\nadd_smalltext|`7Get involved and get rewards!`` Smash an Ultra Pinata once a day during `5Cinco de Mayo Week`` and get a daily reward!|left|\nadd_spacer|small|\nadd_button|claimbutton|Come Back Later|noflags|0|0|\nadd_countdown||center|disable|\nadd_quick_exit|");
							}
							p.CreatePacket(peer);
							break;
							}
							else if (cch == "action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|surgery_reward\n\n") {
							surgery_reward_show(peer);
							break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|password_reply\npassword|") != string::npos) {
								string password = cch.substr(57, cch.length() - 57).c_str();
								string name_ = pInfo(peer)->world;
								vector<World>::iterator pa = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (pa != worlds.end()) {
									World* world_ = &worlds[pa - worlds.begin()];
									WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
									if (block_->fg == 762 && block_->door_id != "") {
										gamepacket_t p;
										p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID);
										replace_str(password, "\n", "");
										transform(password.begin(), password.end(), password.begin(), ::toupper);
										if (block_->door_id != password) p.Insert("`4Wrong password!``");
										else {
											p.Insert(a + "`2The door opens!" + (block_->door_destination == "" ? " But nothing is behind it." : "") + "``");
											if (block_->door_destination != "") {
												gamepacket_t p3(0, pInfo(peer)->netID);
												p3.Insert("OnPlayPositioned"), p3.Insert("audio/door_open.wav"), p3.CreatePacket(peer);
												string door_target = block_->door_destination, door_id = "";
												World target_world = worlds[pa - worlds.begin()];
												int spawn_x = 0, spawn_y = 0;
												if (door_target.find(":") != string::npos) {
													vector<string> detales = explode(":", door_target);
													door_target = detales[0], door_id = detales[1];
												} 
												int ySize = (int)target_world.blocks.size() / 100, xSize = (int)target_world.blocks.size() / ySize;
												if (not door_id.empty()) {
													for (int i_ = 0; i_ < target_world.blocks.size(); i_++) {
														WorldBlock block_data = target_world.blocks[i_];
														if (block_data.fg == 762) continue;
														if (block_data.fg == 1684 or items[block_data.fg].blockType == BlockTypes::DOOR or items[block_data.fg].blockType == BlockTypes::PORTAL) {
															if (block_data.door_id == door_id) {
																spawn_x = i_ % xSize, spawn_y = i_ / xSize;
																break;
															}
														}
													}
												}
												join_world(peer, target_world.name, spawn_x, spawn_y, 250, false, true);

											}
										}
										p.CreatePacket(peer);
									}
								}
								break;
							}
							else if (cch == "action|dialog_return\ndialog_name|2646\nbuttonClicked|off\n\n") {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(peer)->world != pInfo(currentPeer)->world or block_->spotlight != pInfo(currentPeer)->tankIDName) continue;
										pInfo(currentPeer)->spotlight = false, update_clothes(currentPeer);
										gamepacket_t p;
										p.Insert("OnConsoleMessage"), p.Insert("Back to anonymity. (`$In the Spotlight`` mod removed)"), p.CreatePacket(currentPeer);
									}
									gamepacket_t p;
									p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("Lights out!"), p.CreatePacket(peer);
									block_->spotlight = "";
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|dialog_eq_aura") != string::npos) {
								if (pInfo(peer)->eq_a_1 != 0 && !pInfo(peer)->eq_a_update) pInfo(peer)->eq_a = pInfo(peer)->eq_a_1, pInfo(peer)->eq_a_update = true;
								if (pInfo(peer)->eq_a_1 == 0) pInfo(peer)->eq_a_1 = 0, pInfo(peer)->eq_a = 0;
								update_clothes(peer);
								break;
						}
							if (cch.find("action|dialog_return\ndialog_name|dialog_minokawa_wings") != string::npos) {
								bool Minokawa_1 = atoi(explode("\n", explode("checkbox_minokawa_wings|", cch)[1])[0].c_str()), Minokawa_2 = atoi(explode("\n", explode("checkbox_minokawa_pet|", cch)[1])[0].c_str());
								if (Minokawa_1) pInfo(peer)->MKW = true;
								else pInfo(peer)->MKW = false;
								if (Minokawa_2) pInfo(peer)->MKP = true;
								else pInfo(peer)->MKP = false;
								update_clothes(peer);
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|2646\nID|") != string::npos) {
								int netID = atoi(cch.substr(41, cch.length() - 41).c_str());
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									string new_spotlight = "";
									World* world_ = &worlds[p - worlds.begin()];
									WorldBlock* block_ = &world_->blocks[pInfo(peer)->lastwrenchx + (pInfo(peer)->lastwrenchy * 100)];
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(peer)->world != pInfo(currentPeer)->world) continue;
										if (block_->spotlight == pInfo(currentPeer)->tankIDName || pInfo(currentPeer)->netID == netID) {
											if (pInfo(currentPeer)->netID == netID) {
												new_spotlight = pInfo(currentPeer)->tankIDName, pInfo(currentPeer)->spotlight = true;
												gamepacket_t p;
												p.Insert("OnConsoleMessage"), p.Insert("All eyes are on you! (`$In the Spotlight`` mod added)"), p.CreatePacket(currentPeer);
											}
											else {
												gamepacket_t p;
												p.Insert("OnConsoleMessage"), p.Insert("Back to anonymity. (`$In the Spotlight`` mod removed)"), p.CreatePacket(currentPeer);
												pInfo(currentPeer)->spotlight = false;
											}
											if (new_spotlight != "") for (int i_ = 0; i_ < world_->blocks.size(); i_++) if (world_->blocks[i_].spotlight == new_spotlight) world_->blocks[i_].spotlight = "";
											gamepacket_t p;
											p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You shine the light on "+ (new_spotlight == pInfo(peer)->tankIDName ? "yourself" : new_spotlight) + "!"), p.CreatePacket(peer);
											update_clothes(currentPeer);
										}
									}
									block_->spotlight = new_spotlight;
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|worlds_list\nbuttonClicked|s_claimreward") != string::npos) {
								int reward = atoi(cch.substr(72, cch.length() - 72).c_str()), lvl = 0, count = 1;
								vector<int> list{ 6900, 6982, 6212, 3172, 9068, 6912, 10836, 3130, 8284 };
								if (reward <= 0 || reward > list.size()) break;
								if (list[reward - 1] == 10836) count = 100;
								if (list[reward - 1] == 6212) count = 50;
								if (list[reward - 1] == 3172 || list[reward - 1] == 6912) count = 25;
								if (find(pInfo(peer)->surg_p.begin(), pInfo(peer)->surg_p.end(), lvl = reward * 5) == pInfo(peer)->surg_p.end()) {
									if (pInfo(peer)->s_lvl >= lvl) {
										if (modify_inventory(peer, list[reward - 1], count) == 0) {
											pInfo(peer)->surg_p.push_back(lvl);
											packet_(peer, "action|play_sfx\nfile|audio/piano_nice.wav\ndelayMS|0");
											{
												gamepacket_t p;
												p.Insert("OnTalkBubble");
												p.Insert(pInfo(peer)->netID);
												p.Insert("Congratulations! You have received your Surgeon Reward!");
												p.Insert(0), p.Insert(0);
												p.CreatePacket(peer);
											}
											PlayerMoving data_{};
											data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
											BYTE* raw = packPlayerMoving(&data_);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
												if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
												send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw;
											{
												PlayerMoving data_{};
												data_.x = pInfo(peer)->x + 10, data_.y = pInfo(peer)->y + 16, data_.packetType = 19, data_.plantingTree = 100, data_.punchX = list[reward - 1], data_.punchY = pInfo(peer)->netID;
												int32_t to_netid = pInfo(peer)->netID;
												BYTE* raw = packPlayerMoving(&data_);
												raw[3] = 5;
												memcpy(raw + 8, &to_netid, 4);
												send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												delete[] raw;
											}
											surgery_reward_show(peer);
										}
										else {
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("You have full inventory space!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return\ndialog_name|updatefish") != std::string::npos) {
								int x = stoi(explode("|", explode("tilex|", cch)[1])[0]);
								int y = stoi(explode("|", explode("tiley|", cch)[1])[0]);
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									WorldBlock* block_ = &world_->blocks[x + (y * 100)];
									if (cch.find("fishid|") != std::string::npos) {
										int id = stoi(explode("\n", explode("fishid|", cch)[1])[0]);
										if (isValidFish(peer, id)) {
											block_->txt += to_string(id) + "|60|" + to_string(rand() % 5000) + ",";
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
												if (pInfo(peer)->world == pInfo(currentPeer)->world) {
													UpdatePort(currentPeer, x, y, 3002, 3004, block_->txt);
												}
											}
										}
									}
									else if (cch.find("buttonClicked|remove_fish") != std::string::npos) {
										string keren = explode("buttonClicked|remove_fish\n\n", cch)[1];
										keren = explode("\nsinarfish|", keren)[0];
										std::vector<string> lol = explode("\n", keren);
										for (auto& gg : lol) {
											std::vector<string> s = explode("|", gg);
											if (s[1] == "1") {
												auto xd = explode("_", s[0]);
												string newfish = replace1(block_->txt, xd[1] + "|" + xd[2] + "|" + xd[3] + ",", "");
												block_->txt = newfish;
												vz::OnConsoleMessage(peer, "`oRemoved " + xd[2] + "lb. " + items[stoi(xd[1])].name);
												for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
													if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
													if (pInfo(peer)->world == pInfo(currentPeer)->world) {
														UpdatePort(currentPeer, x, y, 3002, 3004, block_->txt);
													}
												}
											}
										}
									}
								}
							}
							else if (cch.find("action|dialog_return\ndialog_name|zombie_purchase\nbuttonClicked|zomb_item_") != string::npos) {
								int item = pInfo(peer)->lockeitem;
								if (item <= 0 || item >= items.size() || items[item].zombieprice == 0) continue;
								int allwl = 0, wl = 0, dl = 0, price = items[item].zombieprice;
								modify_inventory(peer, 4450, wl);
								modify_inventory(peer, 4452, dl);
								allwl = wl + (dl * 100);
								if (allwl >= price) {
									int c_ = 1;
									if (modify_inventory(peer, item, c_) == 0) {
										if (wl >= price) modify_inventory(peer, 4450, price *= -1);
										else {
											modify_inventory(peer, 4450, wl *= -1);
											modify_inventory(peer, 4452, dl *= -1);
											int givedl = (allwl - price) / 100;
											int givewl = (allwl - price) - (givedl * 100);
											modify_inventory(peer, 4450, givewl);
											modify_inventory(peer, 4452, givedl);
										}
										PlayerMoving data_{};
										data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16, data_.packetType = 19, data_.plantingTree = 500, data_.punchX = item, data_.punchY = pInfo(peer)->netID;
										int32_t to_netid = pInfo(peer)->netID;
										BYTE* raw = packPlayerMoving(&data_);
										raw[3] = 5;
										memcpy(raw + 8, &to_netid, 4);
										send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
										delete[] raw;
										gamepacket_t p;
										p.Insert("OnConsoleMessage"), p.Insert("`3You bought " + items[item].name + " for " + setGems(items[item].zombieprice) + " Zombie Brains."), p.CreatePacket(peer);
									}
									else {
										gamepacket_t p;
										p.Insert("OnConsoleMessage"), p.Insert("No inventory space."), p.CreatePacket(peer);
									}
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage"), p.Insert("`9You don't have enough Zombie Brains!``"), p.CreatePacket(peer);
								}
								break;
						}
						else if (cch.find("action|dialog_return\ndialog_name|zurgery_purchase\nbuttonClicked|zurg_item_") != string::npos) {
							int item = pInfo(peer)->lockeitem;
							if (item <= 0 || item >= items.size() || items[item].surgeryprice == 0) continue;
							int allwl = 0, wl = 0, dl = 0, price = items[item].surgeryprice;
							modify_inventory(peer, 4298, wl);
							modify_inventory(peer, 4300, dl);
							allwl = wl + (dl * 100);
							if (allwl >= price) {
								int c_ = 1;
								if (modify_inventory(peer, item, c_) == 0) {
									if (wl >= price) modify_inventory(peer, 4298, price *= -1);
									else {
										modify_inventory(peer, 4298, wl *= -1);
										modify_inventory(peer, 4300, dl *= -1);
										int givedl = (allwl - price) / 100;
										int givewl = (allwl - price) - (givedl * 100);
										modify_inventory(peer, 4298, givewl);
										modify_inventory(peer, 4300, givedl);
									}
									if (item == 1486 && pInfo(peer)->quest_active && pInfo(peer)->quest_step == 6 && pInfo(peer)->quest_progress < 28) {
										pInfo(peer)->quest_progress++;
										if (pInfo(peer)->quest_progress >= 28) {
											pInfo(peer)->quest_progress = 28;
											gamepacket_t p;
											p.Insert("OnTalkBubble");
											p.Insert(pInfo(peer)->netID);
											p.Insert("`9Legendary Quest step complete! I'm off to see a Wizard!");
											p.Insert(0), p.Insert(0);
											p.CreatePacket(peer);
										}
									}
									PlayerMoving data_{};
									data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16, data_.packetType = 19, data_.plantingTree = 500, data_.punchX = item, data_.punchY = pInfo(peer)->netID;
									int32_t to_netid = pInfo(peer)->netID;
									BYTE* raw = packPlayerMoving(&data_);
									raw[3] = 5;
									memcpy(raw + 8, &to_netid, 4);
									send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									delete[] raw;
									gamepacket_t p;
									p.Insert("OnConsoleMessage"), p.Insert("`3You bought " + items[item].name + " for " + setGems(items[item].surgeryprice) + " Caduceus."), p.CreatePacket(peer);
								}
								else {
									gamepacket_t p;
									p.Insert("OnConsoleMessage"), p.Insert("No inventory space."), p.CreatePacket(peer);
								}
							}
							else {
								gamepacket_t p;
								p.Insert("OnConsoleMessage"), p.Insert("`9You don't have enough Caduceus!``"), p.CreatePacket(peer);
							}
							break;
							}

						else if (cch.find("action|dialog_return\ndialog_name|lock_convert\nbuttonClicked|convbgl\n\n") != string::npos) {
							int c8470 = 0, c7188 = 0, additem = 0;
							modify_inventory(peer, 7188, c7188);
							if (c7188 < 100) continue;
							modify_inventory(peer, 8470, c8470);
							if (c8470 >= 200) {
								gamepacket_t p;
								p.Insert("OnTalkBubble");
								p.Insert(pInfo(peer)->netID);
								p.Insert("You don't have room in your backpack!");
								p.Insert(0), p.Insert(1);
								p.CreatePacket(peer);
								{
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("You don't have room in your backpack!");
									p.CreatePacket(peer);
								}
								continue;
							}
							if (c7188 >= 100) {
								if (get_free_slots(pInfo(peer)) >= 2) {
									int cz_ = 1;
									if (modify_inventory(peer, 7188, additem = -100) == 0) {
										modify_inventory(peer, 8470, additem = 1);
										{
											{
												string name_ = pInfo(peer)->world;
												vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
												if (p != worlds.end()) {
													World* world_ = &worlds[p - worlds.begin()];
													PlayerMoving data_{};
													data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16;
													data_.packetType = 19, data_.plantingTree = 500;
													data_.punchX = 8470, data_.punchY = pInfo(peer)->netID;
													int32_t to_netid = pInfo(peer)->netID;
													BYTE* raw = packPlayerMoving(&data_);
													raw[3] = 5;
													memcpy(raw + 8, &to_netid, 4);
													for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
														if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
														if (pInfo(currentPeer)->world == world_->name) {
															send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
														}
													}
													delete[] raw;
												}
											}
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("[`6You spent 100 Blue Gem Lock to get 1 Red Gem Lock``]");
											p.CreatePacket(peer);
										}
									}
									int c_ = 0;
									modify_inventory(peer, 7188, c_);
									gamepacket_t pc;
									pc.Insert("OnTalkBubble");
									pc.Insert(pInfo(peer)->netID);
									pc.Insert("You converted 100 Blue Gem Lock to 1 Red Gem Lock!");
									pc.Insert(0), pc.Insert(1);
									pc.CreatePacket(peer);
								}
							}
							else {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("You don't have enough inventory space!");
								p.CreatePacket(peer);
							}
						}
						else if (cch.find("action|dialog_return\ndialog_name|lock_convert\nbuttonClicked|itslockconvert\n\n") != string::npos) {
						int c7188 = 0, c8470 = 0, additem = 0;
						modify_inventory(peer, 8470, c8470);
						if (c8470 < 1) continue;
						modify_inventory(peer, 7188, c7188);
						if (c7188 >= 101) {
							gamepacket_t p;
							p.Insert("OnTalkBubble");
							p.Insert(pInfo(peer)->netID);
							p.Insert("You don't have room in your backpack!");
							p.Insert(0), p.Insert(1);
							p.CreatePacket(peer);
							{
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("You don't have room in your backpack!");
								p.CreatePacket(peer);
							}
							continue;
						}
						if (c7188 <= 101) {
							if (get_free_slots(pInfo(peer)) >= 2) {
								int cz_ = 1;
								if (modify_inventory(peer, 8470, additem = -1) == 0) {
									modify_inventory(peer, 7188, additem = 100);
									{
										{
											string name_ = pInfo(peer)->world;
											vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
											if (p != worlds.end()) {
												World* world_ = &worlds[p - worlds.begin()];
												PlayerMoving data_{};
												data_.x = pInfo(peer)->lastwrenchx * 32 + 16, data_.y = pInfo(peer)->lastwrenchy * 32 + 16;
												data_.packetType = 19, data_.plantingTree = 500;
												data_.punchX = 8470, data_.punchY = pInfo(peer)->netID;
												int32_t to_netid = pInfo(peer)->netID;
												BYTE* raw = packPlayerMoving(&data_);
												raw[3] = 5;
												memcpy(raw + 8, &to_netid, 4);
												for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
													if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
													if (pInfo(currentPeer)->world == world_->name) {
														send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
													}
												}
												delete[] raw;
											}
										}
										gamepacket_t p;
										p.Insert("OnConsoleMessage");
										p.Insert("[`6You spent 1 Red Gem Lock to get 100 Blue Gem Lock``]");
										p.CreatePacket(peer);
									}
								}
								int c_ = 0;
								modify_inventory(peer, 8470, c_);
								gamepacket_t pc;
								pc.Insert("OnTalkBubble");
								pc.Insert(pInfo(peer)->netID);
								pc.Insert("You converted 1 Red Gem Lock to 100 Blue Gem Lock!");
								pc.Insert(0), pc.Insert(1);
								pc.CreatePacket(peer);
							}
						}
						else {
							gamepacket_t p;
							p.Insert("OnConsoleMessage");
							p.Insert("You don't have enough inventory space!");
							p.CreatePacket(peer);
						}
					}						
							else if (cch.find("action|dialog_return\ndialog_name|billboard_edit\nbillboard_item|") != string::npos) {
								vector<string> t_ = explode("|", cch);
								if (t_.size() < 4) break;
								int billboard_item = atoi(explode("\n", t_[3])[0].c_str());
								if (billboard_item > 0 && billboard_item < items.size()) {
									int got = 0;
									modify_inventory(peer, billboard_item, got);
									if (got == 0) break;
									if (items[billboard_item].untradeable == 1 or billboard_item == 1424 or items[billboard_item].blockType == BlockTypes::LOCK or items[billboard_item].blockType == BlockTypes::FISH) {
										gamepacket_t p, p2;
										p.Insert("OnConsoleMessage"), p.Insert("Item can not be untradeable."), p.CreatePacket(peer);
										p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("Item can not be untradeable."), p2.Insert(0), p2.Insert(1), p2.CreatePacket(peer);
									}
									else {
										pInfo(peer)->b_i = billboard_item;
										if (pInfo(peer)->b_p != 0 && pInfo(peer)->b_i != 0) {
											gamepacket_t p(0, pInfo(peer)->netID);
											p.Insert("OnBillboardChange"), p.Insert(pInfo(peer)->netID), p.Insert(pInfo(peer)->b_i), p.Insert(pInfo(peer)->b_a), p.Insert(pInfo(peer)->b_p), p.Insert(pInfo(peer)->b_w);
											for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
												if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != pInfo(peer)->world) continue;
												p.CreatePacket(currentPeer);
											}
										}
									}
								}
								break;
							}
							else if (cch.find("action|dialog_return") != string::npos) {
								call_dialog(peer, cch);
								break;
								}
						}
						else if (cch.find("action|dialog_return") != string::npos) {
							call_dialog(peer, cch);
							break;
						}
						break;
					}
					case 3: // world/enter
					{
						//auto start = chrono::steady_clock::now();
						if (pInfo(peer)->trading_with != -1) {
							cancel_trade(peer, false);
							break;
						}
						string cch = text_(event.packet);
						if (pInfo(peer)->lpps2 + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
							pInfo(peer)->pps2 = 0;
							pInfo(peer)->lpps2 = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						}
						else {
							pInfo(peer)->pps2++;
							if (pInfo(peer)->pps2 >= 10) {
								//cout << "Over packet 3 limit from " << pInfo(peer)->tankIDName << " in world " << pInfo(peer)->world << " packet was " << cch << endl;
								enet_peer_disconnect_later(peer, 0);
								break;
							}
						}
						if (cch == "action|quit") { // kai quit issaugo dar bus settings ar captcha bypassed disconnect
							if (not pInfo(peer)->tankIDName.empty()) // jeigu yra growid   
								save_player(pInfo(peer)); // issaugoti zaidejo json   
							if (pInfo(peer)->platformid == "0") {
								WindowsAdd - 1;
							}
							if (pInfo(peer)->platformid == "1") {
								iPhoneAdd - 1;
							}
							if (pInfo(peer)->platformid == "2") {
								MacosAdd - 1;
							}
							if (pInfo(peer)->platformid == "3") {
								LinuxAdd - 1;
							}
							if (pInfo(peer)->platformid == "4") {
								AndroidAdd - 1;
							}
							if (pInfo(peer)->platformid == "0,1,1") {
								WindowsAdd - 1;
							}
							if (pInfo(peer)->trading_with != -1) {
								cancel_trade(peer, false);
							}
							char clientConnection[16];
							enet_address_get_host_ip(&peer->address, clientConnection, 16);
							string username = "";
							username = to_lower(pInfo(peer)->tankIDName) + " (" + pInfo(peer)->requestedName + ")";
							cout << "[" << currentDateTime() << "] " << username << " has disconnected with IP: " << clientConnection << endl;
							ofstream myfile;
							enet_peer_disconnect_later(peer, 0); // turetu nesuveikti tada antra karta save
							delete peer->data;
							peer->data = NULL;
						}
						else if (cch == "action|quit_to_exit") {
							if (pInfo(peer)->last_exit + 500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
								pInfo(peer)->last_exit = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
								exit_(peer);
								save_player(pInfo(peer), false);
							}
							else {
								pInfo(peer)->exitwarn++;
							}
							if (pInfo(peer)->exitwarn >= 3) {
								gamepacket_t p;
								p.Insert("OnConsoleMessage");
								p.Insert("`4Bye Duper :D");
								p.CreatePacket(peer);
								add_ipban(peer);
								add_ban(peer, 6.307e+7, "DUPER", "System");
								for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
									gamepacket_t p;
									p.Insert("OnConsoleMessage");
									p.Insert("`4SYSTEM : " + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + " `o Has Been `4BANNED `o For Dupeing!. Play Nice,Everybody");
									p.CreatePacket(currentPeer);
								}
							}
						}
						else
						{
							if (pInfo(peer)->world == "") {
								if (cch.find("action|join_request") != string::npos) {
									if (pInfo(peer)->last_world_enter + 500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
										pInfo(peer)->last_world_enter = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
										vector<string> t_ = explode("|", cch);
										if (t_.size() < 3) break;
										string world_name = explode("\n", t_[2])[0];
										transform(world_name.begin(), world_name.end(), world_name.begin(), ::toupper);
										join_world(peer, world_name);
									}
								}
								else if (cch.find("action|world_button") != string::npos) {
									vector<string> t_ = explode("|", cch);
									if (t_.size() < 3) break;
									string dialog = explode("\n", t_[2])[0];
									if (dialog == "w1_") world_menu(peer);
									else {
										string c_active_worlds = "";
										if (dialog == "_catselect_") {
											c_active_worlds = pInfo(peer)->worlds_owned.size() != 0 ? "\nadd_heading|Your Worlds|" : "\nadd_heading|You don't have any worlds.<CR>|";
											for (int w_ = 0; w_ < (pInfo(peer)->worlds_owned.size() >= 32 ? 32 : pInfo(peer)->worlds_owned.size()); w_++) c_active_worlds += "\nadd_floater|" + pInfo(peer)->worlds_owned[w_] + "|0|0.38|2147418367";
										}
										else if (dialog == "w2_") c_active_worlds = a + "\nadd_heading|" + (top_list_world_menu.empty() ? "The list should update in few minutes" : "Top Worlds") + "|", c_active_worlds += top_list_world_menu;
										else {
											vector<string> worlds;
											if (dialog == "w3_") {
												c_active_worlds = "\nadd_heading|Information|";
												worlds = { "START", "REC", "RECORD", "LOCKETOWN" };
											}
											else {
												c_active_worlds = "\nadd_heading|Shop|";
												worlds = { "VEND", "SET", "SHOP" };
											}
											for (uint8_t i = 0; i < worlds.size(); i++) c_active_worlds += "\nadd_floater|" + worlds[i] + "|" + to_string((i + 1) * -1) + "|0.38|3417414143";
										}
										gamepacket_t p;
										p.Insert("OnRequestWorldSelectMenu"), p.Insert("add_button|Random Worlds|w1_|0.7|3529161471|\nadd_button|Top Worlds|w2_|0.7|3529161471|\nadd_button|Information|w3_|0.7|3529161471|\nadd_button|Shop<CR>|w4_|0.7|3529161471|" + c_active_worlds), p.CreatePacket(peer);
									}
								}
							}
						}
						break;
					}
					case 4:
					{
						//auto start = chrono::steady_clock::now();
						if (pInfo(peer)->lpps23 + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
							pInfo(peer)->pps23 = 0;
							pInfo(peer)->lpps23 = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						}
						else {
							pInfo(peer)->pps23++;
							if (pInfo(peer)->pps23 >= 360) {
								//cout << "Over packet 4 limit from " << pInfo(peer)->tankIDName << " in world " << pInfo(peer)->world << endl;
								enet_peer_disconnect_later(peer, 0);
								break;
							}
						}
						if (pInfo(peer)->tankIDName.empty()) break;
						if (pInfo(peer)->world.empty()) break;
						BYTE* data_ = get_struct(event.packet);
						if (data_ == nullptr) break;
						PlayerMoving* p_ = unpackPlayerMoving(data_);
						add_packet_logs(" [" + pInfo(peer)->ip + "] (" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + " | World: " + pInfo(peer)->world == "" ? "EXIT" : pInfo(peer)->world + ") " + "[PACKET TYPE]: " + to_string(p_->packetType) + " [NetId]: " + to_string(p_->netID) + " [characterState]: " + to_string(p_->characterState) + " [PlantingTree]: " + to_string(p_->plantingTree) + " [X]: " + to_string(p_->x) + " [Y]: " + to_string(p_->y) + "[PunchX]:" + to_string(p_->punchX) + "[PunchY] : " + to_string(p_->punchY) + "");
						switch (p_->packetType) {
						case 0: /*Kai zaidejas pajuda*/
						{
							bool ignore_ = false;
							int currentX = pInfo(peer)->x / 32, currentY = pInfo(peer)->y / 32;
							int targetX = p_->x / 32;
							int targetY = p_->y / 32;

							//if (!pInfo(peer)->superdev) {
							// //p_->characterState == 4 or p_->characterState == 32 or 
								if (p_->characterState == 34 or p_->characterState == 50) {
									CrashTheGameClient(peer);
									enet_peer_disconnect_later(peer, 0);
								//}
							}
							loop_cheat(peer);
							if (pInfo(peer)->last_respawn && !pInfo(peer)->world.empty()) {
								SendRespawn(peer, 0, true);
							}
							if (pInfo(peer)->world.empty()) break;
							if ((int)p_->characterState == 268435472 || (int)p_->characterState == 268435488 || (int)p_->characterState == 268435504 || (int)p_->characterState == 268435616 || (int)p_->characterState == 268435632 || (int)p_->characterState == 268435456 || (int)p_->characterState == 224 || (int)p_->characterState == 112 || (int)p_->characterState == 80 || (int)p_->characterState == 96 || (int)p_->characterState == 224 || (int)p_->characterState == 65584 || (int)p_->characterState == 65712 || (int)p_->characterState == 65696 || (int)p_->characterState == 65536 || (int)p_->characterState == 65552 || (int)p_->characterState == 65568 || (int)p_->characterState == 65680 || (int)p_->characterState == 192 || (int)p_->characterState == 65664 || (int)p_->characterState == 65600 || (int)p_->characterState == 67860 || (int)p_->characterState == 64) {
								if (pInfo(peer)->cheat_bounce == 1) break;
								if (pInfo(peer)->lava_time + 5000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
									pInfo(peer)->lavaeffect = 0;
									pInfo(peer)->lava_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
								}
								else {
									if (pInfo(peer)->lavaeffect >= (pInfo(peer)->feet == 250 ? 7 : 3) || pInfo(peer)->lavaeffect >= (pInfo(peer)->necklace == 5426 ? 7 : 3)) {
										pInfo(peer)->lavaeffect = 0;
										SendRespawn(peer, false, 0, true);
									}
									else pInfo(peer)->lavaeffect++;
								}
							}
							if (pInfo(peer)->fishing_used != 0) {
								if (pInfo(peer)->f_xy != pInfo(peer)->x + pInfo(peer)->y) pInfo(peer)->move_warning++;
								if (pInfo(peer)->move_warning > 1) stop_fishing(peer, true, "Sit still if you wanna fish!");
								if (p_->punchX > 0 && p_->punchY > 0) {
									pInfo(peer)->punch_warning++;
									if (pInfo(peer)->punch_warning >= 2) stop_fishing(peer, false, "");
								}
							}
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								if (pInfo(peer)->x != -1 and pInfo(peer)->y != -1) {
									//try {
									int x_ = (pInfo(peer)->state == 16 ? (int)p_->x / 32 : round((double)p_->x / 32));
									int y_ = (int)p_->y / 32;
									if (x_ < 0 or x_ >= 100 or y_ < 0 or y_ >= 60) continue;
									WorldBlock* block_ = &world_->blocks[x_ + (y_ * 100)];
									if (block_->fg == 1256) pInfo(peer)->hospital_bed = true;
									else pInfo(peer)->hospital_bed = false;
									if (pInfo(peer)->c_x * 32 != (int)p_->x and pInfo(peer)->c_y * 32 != (int)p_->y and not pInfo(peer)->ghost) {
										bool impossible = ar_turi_noclipa(world_, pInfo(peer)->x, pInfo(peer)->y, block_, peer);
										if (impossible) {
											if (items[block_->fg].actionType != 31) {
												gamepacket_t p(0, pInfo(peer)->netID);
												p.Insert("OnSetPos");
												p.Insert(pInfo(peer)->x, pInfo(peer)->y);
												p.CreatePacket(peer);
												pInfo(peer)->hack_++;
												if (pInfo(peer)->hack_ >= 3) {
													enet_peer_disconnect_later(peer, 0);
													//add_ban(peer, 604800, "Hacking", "System");
												}
												break;
											}
										}
									}
									if (block_->fg == 428 and not world_->name.empty() and not pInfo(peer)->OnRace) {
										gamepacket_t p(0, pInfo(peer)->netID), p3(0, pInfo(peer)->netID);
										p3.Insert("OnPlayPositioned");
										p3.Insert("audio/race_start.wav");
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == pInfo(peer)->world) {
												p3.CreatePacket(currentPeer);
											}
										}
										p.Insert("OnRaceStart"), p.CreatePacket(peer);
										pInfo(peer)->OnRace = true;
										pInfo(peer)->Race_Time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
									}
									if (block_->fg == 430 and pInfo(peer)->OnRace and not world_->name.empty()) {
										int time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() - pInfo(peer)->Race_Time;
										gamepacket_t p(0, pInfo(peer)->netID), p2, p3(0, pInfo(peer)->netID);
										p2.Insert("OnConsoleMessage");
										p2.Insert((not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : (pInfo(peer)->d_name.empty() ? pInfo(peer)->name_color : "`0") + "" + (pInfo(peer)->d_name.empty() ? pInfo(peer)->tankIDName : pInfo(peer)->d_name)) + (pInfo(peer)->is_legend ? " of Legend" : "") + " `0finished in `$" + Algorithm::detailMSTime(time) + "`o!``");
										p3.Insert("OnPlayPositioned");
										p3.Insert("audio/race_end.wav");
										for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
											if (pInfo(currentPeer)->world == pInfo(peer)->world) {
												p2.CreatePacket(currentPeer), p3.CreatePacket(currentPeer);
											}
										}
										p.Insert("OnRaceEnd"), p.Insert(time), p.CreatePacket(peer);
										pInfo(peer)->OnRace = false;
										pInfo(peer)->Race_Time = 0;
									}

									if (block_->fg == 1508 and not world_->name.empty()) {
										char blarney_world = world_->name.back();
										if (isdigit(blarney_world)) {
											long long current_time = time(nullptr);
											vector<vector<long long>> av_blarneys = pInfo(peer)->completed_blarneys;
											for (int i_ = 0; i_ < av_blarneys.size(); i_++) {
												int t_blarney_world = av_blarneys[i_][0];
												if ((int)blarney_world - 48 == t_blarney_world) {
													long long blarney_time = av_blarneys[i_][1];
													if (blarney_time - current_time <= 0) {
														av_blarneys[i_][1] = current_time + 86400;
														vector<vector<int>> blarney_prizes{
															//11712 11742 11710 11722
															{11712, 1},{11742, 1},{11710, 1},{11722, 1}, {528, 1},{540, 1},{1514, 5},{1544, 1},{260, 1},{1546, 1},{2400, 1},{2404, 1},{2406, 1},{2414, 1},{2416, 1},{2464, 1},{3428, 1},{3426, 1},{4532, 1},{4528, 1},{4526, 5},{4520, 1},{5740, 1},{5734, 1},{7982, 1},{7992, 1},{7994, 1},{7980, 1},{7998, 1},{7984, 3},{7988, 1},{9416, 1},{9424, 1},{10704, 1},{10680, 1},{10670, 1},{10676, 1}
														};
														vector<int> prize_ = blarney_prizes[rand() % blarney_prizes.size()];
														uint32_t give_id = prize_[0];
														uint32_t give_count = prize_[1];
														int c_ = give_count;
														if (modify_inventory(peer, give_id, c_) != 0) {
															WorldDrop drop_block_{};
															drop_block_.id = give_id, drop_block_.count = give_count, drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = pInfo(peer)->x + rand() % 17, drop_block_.y = pInfo(peer)->y + rand() % 17;
															dropas_(world_, drop_block_);
														}
														int c_2 = 1;
														if (modify_inventory(peer, 1510, c_2) != 0) {
															WorldDrop drop_block_{};
															drop_block_.id = 1510, drop_block_.count = c_2, drop_block_.uid = uint16_t(world_->drop.size()) + 1, drop_block_.x = pInfo(peer)->x + rand() % 17, drop_block_.y = pInfo(peer)->y + rand() % 17;
															dropas_(world_, drop_block_);
														}
														pInfo(peer)->remind_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
														gamepacket_t p;
														p.Insert("OnTalkBubble");
														p.Insert(pInfo(peer)->netID);
														p.Insert("You kissed the " + items[block_->fg].name + " and got a `2" + items[1510].name + "`` and `2" + items[give_id].name + "``");
														p.Insert(1);
														p.CreatePacket(peer);
														{
															gamepacket_t p;
															p.Insert("OnConsoleMessage");
															p.Insert("You kissed the " + items[block_->fg].name + " and got a `2" + items[1510].name + "`` and `2" + items[give_id].name + "``");
															p.CreatePacket(peer);
														}
													}
													else {
														if (pInfo(peer)->remind_time + 8000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
															pInfo(peer)->remind_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
															gamepacket_t p;
															p.Insert("OnTalkBubble");
															p.Insert(pInfo(peer)->netID);
															p.Insert("You will be able to kiss the stone again in " + to_playmod_time(blarney_time - current_time) + "");
															p.Insert(0);
															p.CreatePacket(peer);
														}
													}
													break;
												}
											}
											pInfo(peer)->completed_blarneys = av_blarneys;
										}
									}
									//}
									//catch (out_of_range) { // nuskrido uz worldo
										//cout << "failed to perform anticheat check for player " << pInfo(peer)->tankIDName + " invalid world??" << endl;
									//}
								}
								if (pInfo(peer)->hand == 2286) {
									if (rand() % 100 < 6) {
										pInfo(peer)->geiger_++;
										if (pInfo(peer)->geiger_ >= 100) {
											int c_ = -1;
											modify_inventory(peer, 2286, c_);
											int c_2 = 1;
											modify_inventory(peer, 2204, c_2);
											pInfo(peer)->hand = 2204;
											pInfo(peer)->geiger_ = 0;
											gamepacket_t p;
											p.Insert("OnConsoleMessage");
											p.Insert("You are detecting radiation... (`$Geiger Counting`` mod added)");
											p.CreatePacket(peer);
											packet_(peer, "action|play_sfx\nfile|audio/dialog_confirm.wav\ndelayMS|0");
											update_clothes(peer);
										}
									}
								}
								if (pInfo(peer)->gems > 0 && pInfo(peer)->back == 240) {
									if (pInfo(peer)->x != (int)p_->x) {
										if (pInfo(peer)->i240 + 750 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
											pInfo(peer)->i240 = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
											pInfo(peer)->gems -= 1;
											WorldDrop item_{};
											item_.id = 112, item_.count = 1, item_.x = (int)p_->x + rand() % 17, item_.y = (int)p_->y + rand() % 17, item_.uid = uint16_t(world_->drop.size()) + 1;
											dropas_(world_, item_);
											gamepacket_t p;
											p.Insert("OnSetBux");
											p.Insert(pInfo(peer)->gems);
											p.Insert(0);
											p.Insert((pInfo(peer)->supp >= 1) ? 1 : 0);
											if (pInfo(peer)->supp >= 2) {
												p.Insert((float)33796, (float)1, (float)0);
											}
											p.CreatePacket(peer);
										}
									}
								}
								move_(peer, p_);
								if (pInfo(peer)->x == -1 and pInfo(peer)->y == -1) { /*Atnaujinti clothes nes uzejo i worlda*/
									update_clothes(peer);
									uint32_t my_guild_role = -1;
									if (pInfo(peer)->guild_id != 0) {
										uint32_t guild_id = pInfo(peer)->guild_id;
										vector<Guild>::iterator find_guild = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
										if (find_guild != guilds.end()) {
											Guild* guild_information = &guilds[find_guild - guilds.begin()];
											for (GuildMember member_search : guild_information->guild_members) {
												if (member_search.member_name == pInfo(peer)->tankIDName) {
													my_guild_role = member_search.role_id;
													break;
												}
											}
										}
									}//pertama
									gamepacket_t p3(0, pInfo(peer)->netID);
									p3.Insert("OnSetRoleSkinsAndIcons");
									p3.Insert(pInfo(peer)->roleSkin);
									p3.Insert(pInfo(peer)->roleIcon);
									p3.Insert(0);
									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
										if (pInfo(currentPeer)->world == world_->name) {
											uint32_t guild_id = pInfo(peer)->guild_id;
											vector<Guild>::iterator find_guild = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
											if (find_guild != guilds.end()) {
												Guild* guild_information = &guilds[find_guild - guilds.begin()];
												const auto flag1 = (65536 * guild_information->guild_mascot[1] + guild_information->guild_mascot[0]);
												gamepacket_t p(0, pInfo(peer)->netID);
												p.Insert("OnGuildDataChanged");
												p.Insert(50478);
												p.Insert(79289404);
												p.Insert(flag1);
												p.Insert(my_guild_role);
												p.Insert(0);
												/*gamepacket_t p(0, pInfo(peer)->netID);
												p.Insert("OnGuildDataChanged");
												p.Insert(50478);  //guild_information->guild_mascot[1]
												p.Insert(79289404);
												p.Insert(0), p.Insert(my_guild_role);*/


												/*
												gamepacket_t p2(0, pInfo(peer)->netID);
												p2.Insert("OnCountryState");
												p2.Insert(pInfo(peer)->country + "|showGuild");*/
												p3.CreatePacket(currentPeer);
												if (my_guild_role != -1) {
													p.CreatePacket(currentPeer);
													//p2.CreatePacket(currentPeer);
												}
											}
											if (pInfo(currentPeer)->netID != pInfo(peer)->netID) {
												if (pInfo(currentPeer)->roleSkin != 6 or pInfo(currentPeer)->roleIcon != 6) {
													gamepacket_t p_p(0, pInfo(currentPeer)->netID);
													p_p.Insert("OnSetRoleSkinsAndIcons");
													p_p.Insert(pInfo(currentPeer)->roleSkin);
													p_p.Insert(pInfo(currentPeer)->roleIcon);
													p_p.Insert(0);
													p_p.CreatePacket(peer);
												}
											}
											if (pInfo(currentPeer)->netID != pInfo(peer)->netID and pInfo(currentPeer)->guild_id != 0) {
												uint32_t guild_id = pInfo(currentPeer)->guild_id;
												vector<Guild>::iterator find_guild = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
												if (find_guild != guilds.end()) {
													Guild* guild_information = &guilds[find_guild - guilds.begin()];
													uint32_t my_role = 0;
													for (GuildMember member_search : guild_information->guild_members) {
														if (member_search.member_name == pInfo(currentPeer)->tankIDName) {
															my_role = member_search.role_id;
															break;
														}
													}
													gamepacket_t p(0, pInfo(currentPeer)->netID);
													p.Insert("OnGuildDataChanged");
													p.Insert(50478);
													p.Insert(79289404);
													p.Insert(0), p.Insert(my_role);
													p.CreatePacket(peer);
													{
														gamepacket_t p(0, pInfo(currentPeer)->netID);
														p.Insert("OnCountryState");
														p.Insert(pInfo(currentPeer)->country + "|showGuild");
														p.CreatePacket(peer);
													}
												}
											}
										}
									}
									long long ms_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
									map<string, vector<WorldNPC>>::iterator it;
									for (it = active_npc.begin(); it != active_npc.end(); it++) {
										if (it->first == world_->name) {
											for (int i_ = 0; i_ < it->second.size(); i_++) {
												try {
													WorldNPC npc_ = it->second[i_];
													if (npc_.uid == -1) continue;
													double per_sekunde_praeina_bloku = (double)npc_.projectile_speed / 32;
													double praejo_laiko = (double)(ms_time - npc_.started_moving) / 1000;
													double praejo_distancija = (double)per_sekunde_praeina_bloku * (double)praejo_laiko;
													double current_x = ((int)npc_.kryptis == 180 ? (((double)npc_.x - (double)praejo_distancija) * 32) + 16 : (((double)npc_.x + (double)praejo_distancija) * 32) + 16);
													double current_y = (double)npc_.y * 32;
													bool blocked_ = false;
													if ((int)npc_.kryptis == 180) { // check if it wasnt blocked
														vector<int> new_tiles{};
														if (items[world_->blocks[(int)(current_x / 32) + ((int)(current_y / 32) * 100)].fg].collisionType != 1) {
															new_tiles.push_back((int)(current_x / 32) + ((int)(current_y / 32) * 100));
														} int ySize = world_->blocks.size() / 100, xSize = world_->blocks.size() / ySize;
														vector<WorldBlock> shadow_copy = world_->blocks;
														for (int i2 = 0; i2 < new_tiles.size(); i2++) {
															int x_ = new_tiles[i2] % 100, y_ = new_tiles[i2] / 100;
															if (x_ < 99 and items[shadow_copy[x_ + 1 + (y_ * 100)].fg].collisionType != 1) {
																if (not shadow_copy[x_ + 1 + (y_ * 100)].scanned) {
																	shadow_copy[x_ + 1 + (y_ * 100)].scanned = true;
																	new_tiles.push_back(x_ + 1 + (y_ * 100));
																}
															}
															else if (items[shadow_copy[x_ + 1 + (y_ * 100)].fg].collisionType == 1 and x_ < npc_.x) {
																blocked_ = true;
																break;
															}
														}
													}
													else {
														vector<int> new_tiles{};
														if (items[world_->blocks[(int)(current_x / 32) + ((int)(current_y / 32) * 100)].fg].collisionType != 1) {
															new_tiles.push_back((int)(current_x / 32) + ((int)(current_y / 32) * 100));
														} int ySize = world_->blocks.size() / 100, xSize = world_->blocks.size() / ySize;
														vector<WorldBlock> shadow_copy = world_->blocks;
														for (int i2 = 0; i2 < new_tiles.size(); i2++) {
															int x_ = new_tiles[i2] % 100, y_ = new_tiles[i2] / 100;
															if (x_ < 99 and items[shadow_copy[x_ - 1 + (y_ * 100)].fg].collisionType != 1) {
																if (not shadow_copy[x_ - 1 + (y_ * 100)].scanned) {
																	shadow_copy[x_ - 1 + (y_ * 100)].scanned = true;
																	new_tiles.push_back(x_ - 1 + (y_ * 100));
																}
															}
															else if (items[shadow_copy[x_ - 1 + (y_ * 100)].fg].collisionType == 1 and x_ > npc_.x) {
																blocked_ = true;
																break;
															}
														}
													} if (blocked_) {
														continue;
													}
													PlayerMoving data_{};
													data_.packetType = 34;
													data_.x = (current_x + 16); //nuo x
													data_.y = (current_y + (npc_.id == 8020 ? 6 : 16)); //nuo y
													data_.XSpeed = (current_x + 16); // iki x
													data_.YSpeed = (current_y + (npc_.id == 8020 ? 6 : 16)); // iki y
													data_.punchY = npc_.projectile_speed;
													BYTE* raw = packPlayerMoving(&data_);
													raw[1] = (npc_.id == 8020 ? 15 : 8), raw[2] = npc_.uid, raw[3] = 2;
													memcpy(raw + 40, &npc_.kryptis, 4);
													send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
													delete[] raw;
												}
												catch (out_of_range) {
													continue;
												}
											}
											break;
										}
									}
								}

								pInfo(peer)->x = (int)p_->x, pInfo(peer)->y = (int)p_->y, pInfo(peer)->state = p_->characterState & 0x10;
							}
							break;
						}
						case 3: /* tempat player wrench atau place tile atau hit tile */
					{
						if (p_->punchX < 0 || p_->punchY < 0) break;
						if (p_->punchX > 100 || p_->punchY > 60) break;
						if (p_->plantingTree <= 0 || p_->plantingTree >= items.size()) break;
						if ((pInfo(peer)->dev + pInfo(peer)->owner == 0) && (abs(p_->x / 32 - p_->punchX) > (pInfo(peer)->hand == 11094 ? 6 : 4) || abs(p_->y / 32 - p_->punchY) > (pInfo(peer)->hand == 11094 ? 6 : 4))) break;
						if (p_->plantingTree != 18 and p_->plantingTree != 32) {
							if (pInfo(peer)->Cheat_AF_PlantingTree == 0 and pInfo(peer)->Cheat_AF) {
								if (p_->plantingTree == 5640) pInfo(peer)->isRemote = true;
								pInfo(peer)->Cheat_AF_PunchX = p_->punchX;
								pInfo(peer)->Cheat_AF_PunchY = p_->punchY;
								pInfo(peer)->Cheat_AF_PlantingTree = p_->plantingTree;
								pInfo(peer)->Cheat_AF_isRunning = true;
								if (p_->punchY == pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) pInfo(peer)->isFacingLeft = true;
								}
							}
							int c_ = 0;
							modify_inventory(peer, p_->plantingTree, c_);
							if (c_ == 0) break;
						}
						if (p_->plantingTree == 18) {
							if (pInfo(peer)->punch_time + 100 > (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) break;
							pInfo(peer)->punch_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
							if (has_playmod(pInfo(peer), "Infected!") or pInfo(peer)->hand != 0) pInfo(peer)->last_infected = p_->punchX + (p_->punchY * 100);
						}
						if (pInfo(peer)->trading_with != -1 and p_->packetType != 0 and p_->packetType != 18) {
							cancel_trade(peer, false, true);
							break;
						}
						for (int i = 1; i < 11; i++) {
							std::ifstream configFile("./config/itemDB.json");
							if (!configFile.is_open()) {
								std::cout << "Failed to open config.json" << std::endl;

							}
							nlohmann::json config;
							configFile >> config;
							configFile.close();
							string choose = "item_" + to_string(i);
							int itemid = config[choose]["itemid"].get<int>();
							int j_far = config[choose]["far"].get<int>();
							if (p_->plantingTree == 18 and pInfo(peer)->hand == itemid) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									WorldBlock* block_ = &world_->blocks[p_->punchX + (p_->punchY * 100)];
									if (block_->fg == 0 and block_->bg == 0) break;
								}
								if (p_->punchY == pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										for (int i = 0; i < j_far; i++) {
											edit_tile(peer, p_->punchX - i, p_->punchY, p_->plantingTree);
										}
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										for (int i = 0; i < j_far; i++) {
											edit_tile(peer, p_->punchX + i, p_->punchY, p_->plantingTree);
										}
									}
								}
								else if (p_->punchX == pInfo(peer)->x / 32) {
									if (p_->punchY > pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										for (int i = 0; i < j_far; i++) {
											edit_tile(peer, p_->punchX, p_->punchY + i, p_->plantingTree);
										}
									}
									else if (p_->punchY < pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										for (int i = 0; i < j_far; i++) {
											edit_tile(peer, p_->punchX, p_->punchY - i, p_->plantingTree);
										}
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										for (int i = 0; i < j_far; i++) {
											edit_tile(peer, p_->punchX - i, p_->punchY - i, p_->plantingTree);
										}
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										for (int i = 0; i < j_far; i++) {
											edit_tile(peer, p_->punchX + i, p_->punchY - i, p_->plantingTree);
										}
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										for (int i = 0; i < j_far; i++) {
											edit_tile(peer, p_->punchX - i, p_->punchY - i, p_->plantingTree);
										}
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										for (int i = 0; i < j_far; i++) {
											edit_tile(peer, p_->punchX + i, p_->punchY - i, p_->plantingTree);
										}
									}
								}
								else if (p_->punchY > pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										for (int i = 0; i < j_far; i++) {
											edit_tile(peer, p_->punchX - i, p_->punchY + i, p_->plantingTree);
										}
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										for (int i = 0; i < j_far; i++) {
											edit_tile(peer, p_->punchX + i, p_->punchY + i, p_->plantingTree);
										}
									}
								}
							}
						}

						if (p_->plantingTree == 18 and has_playmod(pInfo(peer), "rayman's fist")) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[p_->punchX + (p_->punchY * 100)];
								if (block_->fg == 0 and block_->bg == 0) break;
							}
							if (p_->punchY == pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchX == pInfo(peer)->x / 32) {
								if (p_->punchY > pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
								}
							}
							else if (p_->punchY > pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
								}
							}
						}
						//10 FAR
						else if (p_->plantingTree == 18 and pInfo(peer)->hand == 9846) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[p_->punchX + (p_->punchY * 100)];
								if (block_->fg == 0 and block_->bg == 0) break;
							}
							if (p_->punchY == pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 7, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 8, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 9, p_->punchY, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 7, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 8, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 9, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchX == pInfo(peer)->x / 32) {
								if (p_->punchY > pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 6, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 7, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 8, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 9, p_->plantingTree);
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 6, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 7, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 8, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 9, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
									edit_tile(peer, p_->punchX - 7, p_->punchY - 7, p_->plantingTree);
									edit_tile(peer, p_->punchX - 8, p_->punchY - 8, p_->plantingTree);
									edit_tile(peer, p_->punchX - 9, p_->punchY - 9, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
									edit_tile(peer, p_->punchX + 7, p_->punchY - 7, p_->plantingTree);
									edit_tile(peer, p_->punchX + 8, p_->punchY - 8, p_->plantingTree);
									edit_tile(peer, p_->punchX + 9, p_->punchY - 9, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
									edit_tile(peer, p_->punchX - 7, p_->punchY - 7, p_->plantingTree);
									edit_tile(peer, p_->punchX - 8, p_->punchY - 8, p_->plantingTree);
									edit_tile(peer, p_->punchX - 9, p_->punchY - 9, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
									edit_tile(peer, p_->punchX + 7, p_->punchY - 7, p_->plantingTree);
									edit_tile(peer, p_->punchX + 8, p_->punchY - 8, p_->plantingTree);
									edit_tile(peer, p_->punchX + 9, p_->punchY - 9, p_->plantingTree);
								}
							}
							else if (p_->punchY > pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY + 6, p_->plantingTree);
									edit_tile(peer, p_->punchX - 7, p_->punchY + 7, p_->plantingTree);
									edit_tile(peer, p_->punchX - 8, p_->punchY + 8, p_->plantingTree);
									edit_tile(peer, p_->punchX - 9, p_->punchY + 9, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY + 6, p_->plantingTree);
									edit_tile(peer, p_->punchX + 7, p_->punchY + 7, p_->plantingTree);
									edit_tile(peer, p_->punchX + 8, p_->punchY + 8, p_->plantingTree);
									edit_tile(peer, p_->punchX + 9, p_->punchY + 9, p_->plantingTree);
								}
							}
						}
						//7 FAR
						else if (p_->plantingTree == 18 and pInfo(peer)->hand == 9906) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[p_->punchX + (p_->punchY * 100)];
								if (block_->fg == 0 and block_->bg == 0) break;
							}
							if (p_->punchY == pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchX == pInfo(peer)->x / 32) {
								if (p_->punchY > pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 6, p_->plantingTree);
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 6, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
								}
							}
							else if (p_->punchY > pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY + 6, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY + 6, p_->plantingTree);
								}
							}
						}
						//10 FAR
						else if (p_->plantingTree == 18 and pInfo(peer)->hand == 9908) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[p_->punchX + (p_->punchY * 100)];
								if (block_->fg == 0 and block_->bg == 0) break;
							}
							if (p_->punchY == pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 7, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 8, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 9, p_->punchY, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 7, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 8, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 9, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchX == pInfo(peer)->x / 32) {
								if (p_->punchY > pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 6, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 7, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 8, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 9, p_->plantingTree);
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 6, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 7, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 8, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 9, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
									edit_tile(peer, p_->punchX - 7, p_->punchY - 7, p_->plantingTree);
									edit_tile(peer, p_->punchX - 8, p_->punchY - 8, p_->plantingTree);
									edit_tile(peer, p_->punchX - 9, p_->punchY - 9, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
									edit_tile(peer, p_->punchX + 7, p_->punchY - 7, p_->plantingTree);
									edit_tile(peer, p_->punchX + 8, p_->punchY - 8, p_->plantingTree);
									edit_tile(peer, p_->punchX + 9, p_->punchY - 9, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
									edit_tile(peer, p_->punchX - 7, p_->punchY - 7, p_->plantingTree);
									edit_tile(peer, p_->punchX - 8, p_->punchY - 8, p_->plantingTree);
									edit_tile(peer, p_->punchX - 9, p_->punchY - 9, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
									edit_tile(peer, p_->punchX + 7, p_->punchY - 7, p_->plantingTree);
									edit_tile(peer, p_->punchX + 8, p_->punchY - 8, p_->plantingTree);
									edit_tile(peer, p_->punchX + 9, p_->punchY - 9, p_->plantingTree);
								}
							}
							else if (p_->punchY > pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY + 6, p_->plantingTree);
									edit_tile(peer, p_->punchX - 7, p_->punchY + 7, p_->plantingTree);
									edit_tile(peer, p_->punchX - 8, p_->punchY + 8, p_->plantingTree);
									edit_tile(peer, p_->punchX - 9, p_->punchY + 9, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY + 6, p_->plantingTree);
									edit_tile(peer, p_->punchX + 7, p_->punchY + 7, p_->plantingTree);
									edit_tile(peer, p_->punchX + 8, p_->punchY + 8, p_->plantingTree);
									edit_tile(peer, p_->punchX + 9, p_->punchY + 9, p_->plantingTree);
								}
							}
						}
						//7 FAR
						else if (p_->plantingTree == 18 and pInfo(peer)->hand == 9770) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[p_->punchX + (p_->punchY * 100)];
								if (block_->fg == 0 and block_->bg == 0) break;
							}
							if (p_->punchY == pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchX == pInfo(peer)->x / 32) {
								if (p_->punchY > pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 6, p_->plantingTree);
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 6, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
								}
							}
							else if (p_->punchY > pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX - 5, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX - 6, p_->punchY + 6, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY + 4, p_->plantingTree);
									edit_tile(peer, p_->punchX + 5, p_->punchY + 5, p_->plantingTree);
									edit_tile(peer, p_->punchX + 6, p_->punchY + 6, p_->plantingTree);
								}
							}
						}						
						//4 FAR
						else if (p_->plantingTree == 18 and pInfo(peer)->hand == 9772) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[p_->punchX + (p_->punchY * 100)];
								if (block_->fg == 0 and block_->bg == 0) break;
							}
							if (p_->punchY == pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchX == pInfo(peer)->x / 32) {
								if (p_->punchY > pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
								}
							}
							else if (p_->punchY > pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
								}
							}
						}
						//5 FAR
						else if (p_->plantingTree == 18 and pInfo(peer)->hand == 9918 or pInfo(peer)->hand == 10290) {
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								WorldBlock* block_ = &world_->blocks[p_->punchX + (p_->punchY * 100)];
								if (block_->fg == 0 and block_->bg == 0) break;
							}
							if (p_->punchY == pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchX == pInfo(peer)->x / 32) {
								if (p_->punchY > pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY + 4, p_->plantingTree);
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX, p_->punchY - 4, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
								}
							}
							else if (p_->punchY < pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
								}
							}
							else if (p_->punchY > pInfo(peer)->y / 32) {
								if (pInfo(peer)->state == 16) {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX - 4, p_->punchY + 4, p_->plantingTree);
								}
								else {
									edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
									edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
									edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
									edit_tile(peer, p_->punchX + 4, p_->punchY + 4, p_->plantingTree);
								}
							}
						}
						else {
							bool empty = false;
							if (p_->plantingTree == 5640) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									for (int i_ = 0; i_ < world_->machines.size(); i_++) {
										WorldMachines machine = world_->machines[i_];
										if (machine.x == pInfo(peer)->magnetron_x and machine.y == pInfo(peer)->magnetron_y and machine.id == 10266) {
											if (machine.enabled) {
												WorldBlock* itemas = &world_->blocks[machine.x + (machine.y * 100)];
												if (itemas->magnetron and itemas->id == pInfo(peer)->magnetron_id) {
													if (itemas->pr > 0) {
														p_->plantingTree = itemas->id;
														//5 FAR
														if (pInfo(peer)->hand == 97701) {
															string name_ = pInfo(peer)->world;
															vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
															if (p_->punchY == pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 4, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 4, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchX == pInfo(peer)->x / 32) {
																if (p_->punchY > pInfo(peer)->y / 32) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 4, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else if (p_->punchY < pInfo(peer)->y / 32) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 4, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY < pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 4, p_->punchY - 4, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 4, p_->punchY - 4, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY < pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 4, p_->punchY - 4, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 4, p_->punchY - 4, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY > pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY + 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 4, p_->punchY + 4, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY + 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 4, p_->punchY + 4, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
														}
														//4 FAR
														else if (pInfo(peer)->hand == 99181) {
															string name_ = pInfo(peer)->world;
															vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
															if (p_->punchY == pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchX == pInfo(peer)->x / 32) {
																if (p_->punchY > pInfo(peer)->y / 32) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 3, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else if (p_->punchY < pInfo(peer)->y / 32) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY < pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY < pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY > pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY + 3, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY + 3, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
														}
														//7 FAR
														else if (pInfo(peer)->hand == 99081) {
															string name_ = pInfo(peer)->world;
															vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
															if (p_->punchY == pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 4, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 5, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 6, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 4, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 5, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 6, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchX == pInfo(peer)->x / 32) {
																if (p_->punchY > pInfo(peer)->y / 32) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 4, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 5, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 6, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else if (p_->punchY < pInfo(peer)->y / 32) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 4, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 5, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 6, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY < pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 4, p_->punchY - 4, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 5, p_->punchY - 5, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 6, p_->punchY - 6, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 4, p_->punchY - 4, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 5, p_->punchY - 5, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 6, p_->punchY - 6, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY < pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 4, p_->punchY - 4, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 5, p_->punchY - 5, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 6, p_->punchY - 6, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY - 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 4, p_->punchY - 4, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 5, p_->punchY - 5, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 6, p_->punchY - 6, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY > pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 3, p_->punchY + 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 4, p_->punchY + 4, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 5, p_->punchY + 5, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 6, p_->punchY + 6, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 3, p_->punchY + 3, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 4, p_->punchY + 4, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 5, p_->punchY + 5, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 6, p_->punchY + 6, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
														}
														//3 FAR
														else if (pInfo(peer)->hand == 97721) {
															string name_ = pInfo(peer)->world;
															vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
															if (p_->punchY == pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchX == pInfo(peer)->x / 32) {
																if (p_->punchY > pInfo(peer)->y / 32) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else if (p_->punchY < pInfo(peer)->y / 32) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY < pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY < pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY - 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY - 2, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
															else if (p_->punchY > pInfo(peer)->y / 32) {
																if (pInfo(peer)->state == 16) {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 1, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX - 2, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
																else {
																	if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 1, p_->punchY + 1, itemas->id, true)) itemas->pr--;
																	if (edit_tile(peer, p_->punchX + 2, p_->punchY + 2, itemas->id, true)) itemas->pr--;
																	if (itemas->pr <= 0) {
																		PlayerMoving data_{};
																		data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																		BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																		BYTE* blc = raw + 56;
																		form_visual(blc, *itemas, *world_, NULL, false);
																		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																			if (pInfo(currentPeer)->world == world_->name) {
																				send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																			}
																		}
																		delete[] raw, blc;
																	}
																	break;
																}
															}
														}
														else if (edit_tile(peer, p_->punchX, p_->punchY, itemas->id, true)) {
															itemas->pr--;
															if (itemas->pr <= 0) {
																PlayerMoving data_{};
																data_.packetType = 5, data_.punchX = machine.x, data_.punchY = machine.y, data_.characterState = 0x8;
																BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, itemas));
																BYTE* blc = raw + 56;
																form_visual(blc, *itemas, *world_, NULL, false);
																for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																	if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																	if (pInfo(currentPeer)->world == world_->name) {
																		send_raw(currentPeer, 4, raw, 112 + alloc_(world_, itemas), ENET_PACKET_FLAG_RELIABLE);
																	}
																}
																delete[] raw, blc;
															}
															break;
														}
													}
													else {
														empty = true;
														gamepacket_t p;
														p.Insert("OnTalkBubble");
														p.Insert(pInfo(peer)->netID);
														p.Insert("The `2" + items[machine.id].name + "`` is empty!");
														p.Insert(0), p.Insert(0);
														p.CreatePacket(peer);
													}
												}
											}
											break;
										}
									}
								} if (p_->plantingTree == 5640 and not empty) {
									gamepacket_t p;
									p.Insert("OnTalkBubble");
									p.Insert(pInfo(peer)->netID);
									p.Insert("There is no active `2" + items[10266].name + "``!");
									p.Insert(0), p.Insert(0);
									p.CreatePacket(peer);
								}
								break;
							}
							int adaBrp = 0;//ats
							modify_inventory(peer, p_->plantingTree, adaBrp);
							if (pInfo(peer)->hand == 9918 and adaBrp >= 5) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p_->punchY == pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchX == pInfo(peer)->x / 32) {
									if (p_->punchY > pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 4, p_->plantingTree);
									}
									else if (p_->punchY < pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 4, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
									}
								}
								else if (p_->punchY > pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY + 4, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY + 4, p_->plantingTree);
									}
								}
							}
							else if (pInfo(peer)->hand == 9772 and adaBrp >= 4) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p_->punchY == pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchX == pInfo(peer)->x / 32) {
									if (p_->punchY > pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
									}
									else if (p_->punchY < pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
									}
								}
								else if (p_->punchY > pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
									}
								}
							}
							else if (pInfo(peer)->hand == 9770 and adaBrp >= 7) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p_->punchY == pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchX == pInfo(peer)->x / 32) {
									if (p_->punchY > pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 6, p_->plantingTree);
									}
									else if (p_->punchY < pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 6, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
									}
								}
								else if (p_->punchY > pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY + 6, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY + 6, p_->plantingTree);
									}
								}
							}
							else if (pInfo(peer)->hand == 9906 and adaBrp >= 7) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p_->punchY == pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchX == pInfo(peer)->x / 32) {
									if (p_->punchY > pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 6, p_->plantingTree);
									}
									else if (p_->punchY < pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 6, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
									}
								}
								else if (p_->punchY > pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY + 6, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY + 6, p_->plantingTree);
									}
								}
							}							
							else if (pInfo(peer)->hand == 9908 and adaBrp >= 10) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p_->punchY == pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 7, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 8, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 9, p_->punchY, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 7, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 8, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 9, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchX == pInfo(peer)->x / 32) {
									if (p_->punchY > pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 6, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 7, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 8, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 9, p_->plantingTree);
									}
									else if (p_->punchY < pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 6, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 7, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 8, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 9, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
										edit_tile(peer, p_->punchX - 7, p_->punchY - 7, p_->plantingTree);
										edit_tile(peer, p_->punchX - 8, p_->punchY - 8, p_->plantingTree);
										edit_tile(peer, p_->punchX - 9, p_->punchY - 9, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
										edit_tile(peer, p_->punchX + 7, p_->punchY - 7, p_->plantingTree);
										edit_tile(peer, p_->punchX + 8, p_->punchY - 8, p_->plantingTree);
										edit_tile(peer, p_->punchX + 9, p_->punchY - 9, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
										edit_tile(peer, p_->punchX - 7, p_->punchY - 7, p_->plantingTree);
										edit_tile(peer, p_->punchX - 8, p_->punchY - 8, p_->plantingTree);
										edit_tile(peer, p_->punchX - 9, p_->punchY - 9, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
										edit_tile(peer, p_->punchX + 7, p_->punchY - 7, p_->plantingTree);
										edit_tile(peer, p_->punchX + 8, p_->punchY - 8, p_->plantingTree);
										edit_tile(peer, p_->punchX + 9, p_->punchY - 9, p_->plantingTree);
									}
								}
								else if (p_->punchY > pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY + 6, p_->plantingTree);
										edit_tile(peer, p_->punchX - 7, p_->punchY + 7, p_->plantingTree);
										edit_tile(peer, p_->punchX - 8, p_->punchY + 8, p_->plantingTree);
										edit_tile(peer, p_->punchX - 9, p_->punchY + 9, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY + 6, p_->plantingTree);
										edit_tile(peer, p_->punchX + 7, p_->punchY + 7, p_->plantingTree);
										edit_tile(peer, p_->punchX + 8, p_->punchY + 8, p_->plantingTree);
										edit_tile(peer, p_->punchX + 9, p_->punchY + 9, p_->plantingTree);
									}
								}
							}
							else if (pInfo(peer)->hand == 9846 and adaBrp >= 10) {
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p_->punchY == pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 7, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 8, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 9, p_->punchY, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 7, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 8, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 9, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchX == pInfo(peer)->x / 32) {
									if (p_->punchY > pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 6, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 7, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 8, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY + 9, p_->plantingTree);
									}
									else if (p_->punchY < pInfo(peer)->y / 32) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 6, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 7, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 8, p_->plantingTree);
										edit_tile(peer, p_->punchX, p_->punchY - 9, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
										edit_tile(peer, p_->punchX - 7, p_->punchY - 7, p_->plantingTree);
										edit_tile(peer, p_->punchX - 8, p_->punchY - 8, p_->plantingTree);
										edit_tile(peer, p_->punchX - 9, p_->punchY - 9, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
										edit_tile(peer, p_->punchX + 7, p_->punchY - 7, p_->plantingTree);
										edit_tile(peer, p_->punchX + 8, p_->punchY - 8, p_->plantingTree);
										edit_tile(peer, p_->punchX + 9, p_->punchY - 9, p_->plantingTree);
									}
								}
								else if (p_->punchY < pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY - 6, p_->plantingTree);
										edit_tile(peer, p_->punchX - 7, p_->punchY - 7, p_->plantingTree);
										edit_tile(peer, p_->punchX - 8, p_->punchY - 8, p_->plantingTree);
										edit_tile(peer, p_->punchX - 9, p_->punchY - 9, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY - 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY - 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY - 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY - 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY - 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY - 6, p_->plantingTree);
										edit_tile(peer, p_->punchX + 7, p_->punchY - 7, p_->plantingTree);
										edit_tile(peer, p_->punchX + 8, p_->punchY - 8, p_->plantingTree);
										edit_tile(peer, p_->punchX + 9, p_->punchY - 9, p_->plantingTree);
									}
								}
								else if (p_->punchY > pInfo(peer)->y / 32) {
									if (pInfo(peer)->state == 16) {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX - 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX - 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX - 3, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX - 4, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX - 5, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX - 6, p_->punchY + 6, p_->plantingTree);
										edit_tile(peer, p_->punchX - 7, p_->punchY + 7, p_->plantingTree);
										edit_tile(peer, p_->punchX - 8, p_->punchY + 8, p_->plantingTree);
										edit_tile(peer, p_->punchX - 9, p_->punchY + 9, p_->plantingTree);
									}
									else {
										edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
										edit_tile(peer, p_->punchX + 1, p_->punchY + 1, p_->plantingTree);
										edit_tile(peer, p_->punchX + 2, p_->punchY + 2, p_->plantingTree);
										edit_tile(peer, p_->punchX + 3, p_->punchY + 3, p_->plantingTree);
										edit_tile(peer, p_->punchX + 4, p_->punchY + 4, p_->plantingTree);
										edit_tile(peer, p_->punchX + 5, p_->punchY + 5, p_->plantingTree);
										edit_tile(peer, p_->punchX + 6, p_->punchY + 6, p_->plantingTree);
										edit_tile(peer, p_->punchX + 7, p_->punchY + 7, p_->plantingTree);
										edit_tile(peer, p_->punchX + 8, p_->punchY + 8, p_->plantingTree);
										edit_tile(peer, p_->punchX + 9, p_->punchY + 9, p_->plantingTree);
									}
								}
							}
							
							else edit_tile(peer, p_->punchX, p_->punchY, p_->plantingTree);
						}
						break;
					}
					case 7: /*Kai zaidejas ieina pro duris arba portal*/ /*2/16/2022 update: cia dar gali buti STEAM USE*/
						{
						string name_ = pInfo(peer)->world;
						vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
						if (p != worlds.end()) {
							World* world_ = &worlds[p - worlds.begin()];
							//try {
							if (p_->punchX < 0 or p_->punchX >= 100 or p_->punchY < 0 or p_->punchY >= 60) {
								packet_(peer, "`4ngapain dek?");
								add_ban(peer, 604800, "Try to crash Adventure", "System");
								cout << "crash try by " << pInfo(peer)->tankIDName << endl;
								//return false;
							}//okok
							WorldBlock* block_ = &world_->blocks[p_->punchX + (p_->punchY * 100)];
									bool impossible = ar_turi_noclipa(world_, pInfo(peer)->x, pInfo(peer)->y, block_, peer);
									if (impossible) break;
									if (items[items[block_->fg ? block_->fg : block_->bg].id].blockType == BlockTypes::CHECKPOINT) {
										pInfo(peer)->c_x = p_->punchX, pInfo(peer)->c_y = p_->punchY;
										gamepacket_t p(0, pInfo(peer)->netID);
										p.Insert("SetRespawnPos");
										p.Insert(pInfo(peer)->c_x + (pInfo(peer)->c_y * 100));
										p.CreatePacket(peer);
									}
									else if (items[block_->fg ? block_->fg : block_->bg].id == 6) exit_(peer);
									else if (block_->fg == 4722 && pInfo(peer)->adventure_begins == false) {
										pInfo(peer)->adventure_begins = true;
										gamepacket_t p(0);
										p.Insert("OnAddNotification"), p.Insert("interface/large/adventure.rttex"), p.Insert(block_->heart_monitor), p.Insert("audio/gong.wav"), p.Insert(0), p.CreatePacket(peer);
									}
									else if (items[block_->fg ? block_->fg : block_->bg].id == 6) exit_(peer);
									else if (block_->fg == 4722 && pInfo(peer)->adventure_begins == false) {
										pInfo(peer)->adventure_begins = true;
										gamepacket_t p(0);
										p.Insert("OnAddNotification"), p.Insert("interface/large/adventure.rttex"), p.Insert(block_->heart_monitor), p.Insert("audio/gong.wav"), p.Insert(0), p.CreatePacket(peer);
									}
									else if (items[block_->fg ? block_->fg : block_->bg].id == 6) exit_(peer);
									else if (items[block_->fg].blockType == BlockTypes::DOOR or items[block_->fg].blockType == BlockTypes::PORTAL) {
										string door_target = block_->door_destination, door_id = "";
										World target_world = worlds[p - worlds.begin()];
										bool locked = (block_->open ? false : (target_world.owner_name == pInfo(peer)->tankIDName or pInfo(peer)->dev or target_world.open_to_public or target_world.owner_name.empty() or (guild_access(peer, target_world.guild_id) or find(target_world.admins.begin(), target_world.admins.end(), pInfo(peer)->tankIDName) != target_world.admins.end()) ? false : true));
										int spawn_x = 0, spawn_y = 0;
										if (not locked && block_->fg != 762) {
											if (door_target.find(":") != string::npos) {
												vector<string> detales = explode(":", door_target);
												door_target = detales[0], door_id = detales[1];
											} if (not door_target.empty() and door_target != world_->name) {
												if (not check_name(door_target)) {
													gamepacket_t p(250, pInfo(peer)->netID);
													p.Insert("OnSetFreezeState");
													p.Insert(1);
													p.CreatePacket(peer);
													{
														gamepacket_t p(250);
														p.Insert("OnConsoleMessage");
														p.Insert(door_target);
														p.CreatePacket(peer);
													}
													{
														gamepacket_t p(250);
														p.Insert("OnZoomCamera");
														p.Insert((float)10000.000000);
														p.Insert(1000);
														p.CreatePacket(peer);
													}
													{
														gamepacket_t p(250, pInfo(peer)->netID);
														p.Insert("OnSetFreezeState");
														p.Insert(0);
														p.CreatePacket(peer);
													}
													break;
												}
												target_world = get_world(door_target);
											}
											int ySize = (int)target_world.blocks.size() / 100, xSize = (int)target_world.blocks.size() / ySize, square = (int)target_world.blocks.size();
											if (not door_id.empty()) {
												for (int i_ = 0; i_ < target_world.blocks.size(); i_++) {
													WorldBlock block_data = target_world.blocks[i_];
													if (block_data.fg == 1684 or items[block_data.fg].blockType == BlockTypes::DOOR or items[block_data.fg].blockType == BlockTypes::PORTAL) {
														if (block_data.door_id == door_id) {
															spawn_x = i_ % xSize, spawn_y = i_ / xSize;
															break;
														}
													}
												}
											}
										}
										if (block_->fg == 762) {
											pInfo(peer)->lastwrenchx = p_->punchX, pInfo(peer)->lastwrenchy = p_->punchY;
											gamepacket_t p2;
											if (block_->door_id == "") p2.Insert("OnTalkBubble"), p2.Insert(pInfo(peer)->netID), p2.Insert("No password has been set yet!"), p2.Insert(0), p2.Insert(1);
											else p2.Insert("OnDialogRequest"), p2.Insert("set_default_color|`o\nadd_label_with_icon|big|`wPassword Door``|left|762|\nadd_textbox|The door requires a password.|left|\nadd_text_input|password|Password||24|\nend_dialog|password_reply|Cancel|OK|");
											p2.CreatePacket(peer);
											gamepacket_t p(250, pInfo(peer)->netID), p3(250), p4(250, pInfo(peer)->netID);
											p.Insert("OnSetFreezeState"), p.Insert(1), p.CreatePacket(peer);
											p3.Insert("OnZoomCamera"), p3.Insert((float)10000.000000), p3.Insert(1000), p3.CreatePacket(peer);
											p4.Insert("OnSetFreezeState"), p4.Insert(0), p4.CreatePacket(peer);
										}
										if (block_->fg != 762) join_world(peer, target_world.name, spawn_x, spawn_y, 250, locked, true);
									}
									else {
										switch (block_->fg) {
											case 3270: case 3496:
											{
												Position2D steam_connector = track_steam(world_, block_, p_->punchX, p_->punchY);
												if (steam_connector.x != -1 and steam_connector.y != -1) {
													WorldBlock* block_s = &world_->blocks[steam_connector.x + (steam_connector.y * 100)];
													switch (block_s->fg) {
														case 3286: //steam door
														{
															block_s->flags = (block_s->flags & 0x00400000 ? block_s->flags ^ 0x00400000 : block_s->flags | 0x00400000);
															PlayerMoving data_{};
															data_.packetType = 5, data_.punchX = steam_connector.x, data_.punchY = steam_connector.y, data_.characterState = 0x8;
															BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, block_s));
															BYTE* blc = raw + 56;
															form_visual(blc, *block_s, *world_, peer, false);
															for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																if (pInfo(currentPeer)->world == world_->name) {
																	send_raw(currentPeer, 4, raw, 112 + alloc_(world_, block_s), ENET_PACKET_FLAG_RELIABLE);
																}
															}
															delete[] raw, blc;
															break;
														}
														case 3724: // spirit storage unit
														{
															uint32_t scenario = 20;
															{
																// check for ghost jars
																for (int i = 0; i < world_->drop.size(); i++) {
																	WorldDrop* check_drop = &world_->drop[i];
																	Position2D dropped_at{ check_drop->x / 32, check_drop->y / 32 };
																	if (dropped_at.x == steam_connector.x and dropped_at.y == steam_connector.y) {
																		if (check_drop->id == 3722) {
																			uint32_t explo_chance = check_drop->count;
																			// remove drop
																			{
																				PlayerMoving data_{};
																				data_.packetType = 14, data_.netID = -2, data_.plantingTree = check_drop->uid;
																				BYTE* raw = packPlayerMoving(&data_);
																				int32_t item = -1;
																				memcpy(raw + 8, &item, 4);
																				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																					if (pInfo(currentPeer)->world == name_) {
																						send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																					}
																				}
																				world_->drop[i].id = 0, world_->drop[i].x = -1, world_->drop[i].y = -1;
																				delete[] raw;
																			}
																			block_s->c_ += explo_chance;
																			// explode or not
																			{
																				if (block_s->c_ * 5 >= 105) {
																					float explosion_chance = (float)((block_s->c_ * 5) - 100) * 0.5;
																					if (explosion_chance > rand() % 100) {
																						//bam bam
																						block_s->fg = 3726;
																						// drop the prize
																						{
																							vector<int> all_p{ 3734, 3732, 3748, 3712, 3706, 3708, 3718, 11136, 3728, 10056, 3730, 3788, 3750, 3738, 6060, 3738, 6840, 3736, 3750 };
																							uint32_t prize = 0;
																							if (block_s->c_ * 5 <= 115) prize = 3734;
																							else if (block_s->c_ * 5 <= 130) prize = 3732;
																							else if (block_s->c_ * 5 <= 140) prize = 3748;
																							else if (block_s->c_ * 5 <= 170) {
																								vector<int> p_drops = {
																									3712, 3706, 3708, 3718, 11136
																								};
																								prize = p_drops[rand() % p_drops.size()];
																							}
																							else if (block_s->c_ * 5 <= 190)  prize = 3728;
																							else if (block_s->c_ * 5 <= 205)  prize = 10056;
																							else if (block_s->c_ * 5 <= 220)  prize = 3730;
																							else if (block_s->c_ * 5 == 225)  prize = 3788;
																							else if (block_s->c_ * 5 <= 240)  prize = 3750;
																							else if (block_s->c_ * 5 == 245)  prize = 3738;
																							else if (block_s->c_ * 5 <= 255)  prize = 6060;
																							else if (block_s->c_ * 5 <= 265 or explo_chance * 5 >= 265) {
																								if (explo_chance * 5 >= 265) prize = all_p[rand() % all_p.size()];
																								else prize = 3738;
																							}
																							else {
																								vector<int> p_drops = {
																									6840
																								};
																								if (block_s->c_ * 5 >= 270) p_drops.push_back(3736);
																								if (block_s->c_ * 5 >= 295) p_drops.push_back(3750);
																								prize = p_drops[rand() % p_drops.size()];
																							} if (prize != 0) {
																								WorldDrop drop_block_{};
																								drop_block_.x = steam_connector.x * 32 + rand() % 17;
																								drop_block_.y = steam_connector.y * 32 + rand() % 17;
																								drop_block_.id = prize, drop_block_.count = 1, drop_block_.uid = uint16_t(world_->drop.size()) + 1;
																								dropas_(world_, drop_block_);
																								{
																									PlayerMoving data_{};
																									data_.packetType = 0x11, data_.x = steam_connector.x * 32 + 16, data_.y = steam_connector.y * 32 + 16;
																									data_.YSpeed = 97, data_.XSpeed = 3724;
																									BYTE* raw = packPlayerMoving(&data_);
																									PlayerMoving data_2{};
																									data_2.packetType = 0x11, data_2.x = steam_connector.x * 32 + 16, data_2.y = steam_connector.y * 32 + 16;
																									data_2.YSpeed = 108;
																									BYTE* raw2 = packPlayerMoving(&data_2);
																									gamepacket_t p;
																									p.Insert("OnConsoleMessage");
																									p.Insert("`#[A `9Spirit Storage Unit`` exploded, bringing forth an `9" + items[prize].name + "`` from The Other Side!]``");
																									for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																										if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																										if (pInfo(currentPeer)->world == world_->name) {
																											p.CreatePacket(currentPeer);
																											send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																											send_raw(currentPeer, 4, raw2, 56, ENET_PACKET_FLAG_RELIABLE);
																										}
																									}
																									delete[] raw, raw2;
																								}
																								scenario = 22;
																							}
																						}
																						block_s->c_ = 0;
																					}
																				}
																			}
																			// update visuals
																			{
																				PlayerMoving data_{};
																				data_.packetType = 5, data_.punchX = steam_connector.x, data_.punchY = steam_connector.y, data_.characterState = 0x8;
																				BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, block_s));
																				BYTE* blc = raw + 56;
																				form_visual(blc, *block_s, *world_, peer, false);
																				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																					if (pInfo(currentPeer)->world == world_->name) {
																						send_raw(currentPeer, 4, raw, 112 + alloc_(world_, block_s), ENET_PACKET_FLAG_RELIABLE);
																					}
																				}
																				delete[] raw, blc;
																			}
																			break;
																		}
																	}
																}
															}
															PlayerMoving data_{};
															data_.packetType = 32; // steam update paketas
															data_.punchX = steam_connector.x;
															data_.punchY = steam_connector.y;
															BYTE* raw = packPlayerMoving(&data_);
															raw[3] = scenario;
															for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
																if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
																if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
																send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
															}
															delete[] raw;
															break;
														}
														default:
															break;
													}
												}
												PlayerMoving data_{};
												data_.packetType = 32; // steam update paketas
												data_.punchX = p_->punchX;
												data_.punchY = p_->punchY;
												BYTE* raw = packPlayerMoving(&data_);
												for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
													if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
													if (pInfo(peer)->world != pInfo(currentPeer)->world) continue;
													send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												}
												delete[] raw;
												break;
											}
											default:
												break;
										}
									}
								}
								//catch (out_of_range& klaida) {
									//cout << "case 7 klaida -> " << klaida.what() << endl;
								//}
							//}
							break;
						}
						case 10: /*Kai zaidejas paspaudzia du kartus ant inventory itemo*/
						{
							if (pInfo(peer)->trading_with != -1) {
								cancel_trade(peer, false);
								break;
							}
							if (p_->plantingTree <= 0 or p_->plantingTree >= items.size()) break;
							int c_ = 0;
							modify_inventory(peer, p_->plantingTree, c_);
							if (c_ == 0) break;
							if (items[p_->plantingTree].blockType != BlockTypes::CLOTHING) {
								int free = get_free_slots(pInfo(peer)), slot = 1;
								int c242 = 242, c1796 = 1796, c6802 = 6802, c1486 = 1486, countofused = 0, getdl = 1, getwl = 100, removewl = -100, removedl = -1, countwl = 0, c4450 = 4450, c4452 = 4452;
								int c4298 = 4298, c4300 = 4300;
								int c7188 = 7188;
								modify_inventory(peer, p_->plantingTree, countofused);
								if (free >= slot) {
									if (p_->plantingTree == 242 || p_->plantingTree == 1796) {
										modify_inventory(peer, p_->plantingTree == 242 ? c1796 : c242, countwl);
										if (p_->plantingTree == 242 ? countwl <= 199 : countwl <= 100) {
											if (p_->plantingTree == 242 ? countofused >= 100 : countofused >= 1) {
												modify_inventory(peer, p_->plantingTree == 242 ? c242 : c1796, p_->plantingTree == 242 ? removewl : removedl);
												modify_inventory(peer, p_->plantingTree == 242 ? c1796 : c242, p_->plantingTree == 242 ? getdl : getwl);
												gamepacket_t p, p2;
												p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(p_->plantingTree == 242 ? "You compressed 100 `2World Lock`` into a `2Diamond Lock``!" : "You shattered a `2Diamond Lock`` into 100 `2World Lock``!"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
												p2.Insert("OnConsoleMessage"), p2.Insert(p_->plantingTree == 242 ? "You compressed 100 `2World Lock`` into a `2Diamond Lock``!" : "You shattered a `2Diamond Lock`` into 100 `2World Lock``!"), p2.CreatePacket(peer);
											}
										}
									}
									else if (p_->plantingTree == 7188) {
										modify_inventory(peer, c1796, countwl);
										if (countwl <= 100) {
											if (countofused >= 1) {
												modify_inventory(peer, c7188, removedl);
												modify_inventory(peer, c1796, getwl);
												gamepacket_t p, p2;
												p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert("You shattered a `2Blue Gem Lock`` into 100 `2Diamond Lock``!"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
												p2.Insert("OnConsoleMessage"), p2.Insert("You shattered a `2Blue Gem Lock`` into 100 `2Diamond Lock``!"), p2.CreatePacket(peer);
											}
										}
									}
									else if (p_->plantingTree == 1486 || p_->plantingTree == 6802) {
										modify_inventory(peer, p_->plantingTree == 1486 ? c6802 : c1486, countwl);
										if (p_->plantingTree == 1486 ? countwl <= 199 : countwl <= 100) {
											if (p_->plantingTree == 1486 ? countofused >= 100 : countofused >= 1) {
												modify_inventory(peer, p_->plantingTree == 1486 ? c1486 : c6802, p_->plantingTree == 1486 ? removewl : removedl);
												modify_inventory(peer, p_->plantingTree == 1486 ? c6802 : c1486, p_->plantingTree == 1486 ? getdl : getwl);
												gamepacket_t p, p2;
												p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(p_->plantingTree == 1486 ? "You compressed 100 `2Growtoken`` into a `2Mega Growtoken``!" : "You shattered a `2Mega Growtoken`` into 100 `2Growtoken``!"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
												p2.Insert("OnConsoleMessage"), p2.Insert(p_->plantingTree == 1486 ? "You compressed 100 `2Growtoken`` into a `2Mega Growtoken``!" : "You shattered a `2Mega Growtoken`` into 100 `2Growtoken``!"), p2.CreatePacket(peer);
											}
										}
									}
									else if (p_->plantingTree == 4450 || p_->plantingTree == 4452) {
										modify_inventory(peer, p_->plantingTree == 4450 ? c4452 : c4450, countwl);
										if (p_->plantingTree == 4450 ? countwl <= 199 : countwl <= 100) {
											if (p_->plantingTree == 4450 ? countofused >= 100 : countofused >= 1) {
												modify_inventory(peer, p_->plantingTree == 4450 ? c4450 : c4452, p_->plantingTree == 4450 ? removewl : removedl);
												modify_inventory(peer, p_->plantingTree == 4450 ? c4452 : c4450, p_->plantingTree == 4450 ? getdl : getwl);
												gamepacket_t p, p2;
												p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(p_->plantingTree == 4450 ? "You compressed 100 `2Zombie Brain`` into a `2Pile of Zombie Brains``!" : "You shattered a `2Pile of Zombie Brains`` into 100 `2Zombie Brain``!"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
												p2.Insert("OnConsoleMessage"), p2.Insert(p_->plantingTree == 4450 ? "You compressed 100 `2Zombie Brain`` into a `2Pile of Zombie Brains``!" : "You shattered a `2Pile of Zombie Brains`` into 100 `2Zombie Brain``!"), p2.CreatePacket(peer);
											}
										}
									}
									else if (p_->plantingTree == 4298 || p_->plantingTree == 4300) {
										modify_inventory(peer, p_->plantingTree == 4298 ? c4300 : c4298, countwl);
										if (p_->plantingTree == 4298 ? countwl <= 199 : countwl <= 100) {
											if (p_->plantingTree == 4298 ? countofused >= 100 : countofused >= 1) {
												modify_inventory(peer, p_->plantingTree == 4298 ? c4298 : c4300, p_->plantingTree == 4298 ? removewl : removedl);
												modify_inventory(peer, p_->plantingTree == 4298 ? c4300 : c4298, p_->plantingTree == 4298 ? getdl : getwl);
												gamepacket_t p, p2;
												p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(p_->plantingTree == 4298 ? "You compressed 100 `2Caduceus`` into a `2Golden Caduceus``!" : "You shattered a `2Golden Caduceus`` into 100 `2Caduceus``!"), p.Insert(0), p.Insert(1), p.CreatePacket(peer);
												p2.Insert("OnConsoleMessage"), p2.Insert(p_->plantingTree == 4298 ? "You compressed 100 `2Caduceus`` into a `2Golden Caduceus``!" : "You shattered a `2Golden Caduceus`` into 100 `2Caduceus``!"), p2.CreatePacket(peer);
											}
										}
									}
								}
								/*compress ir t.t*/
								break;
							}
							/*equip*/
							equip_clothes(peer, p_->plantingTree);
							break;
						}
						case 11: /*Kai zaidejas paema isdropinta itema*/
						{
							if (p_->x < 0 || p_->y <0) break;
							bool displaybox = true;
							string name_ = pInfo(peer)->world;
							vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
							if (p != worlds.end()) {
								World* world_ = &worlds[p - worlds.begin()];
								for (int i_ = 0; i_ < world_->drop.size(); i_++) {
									if (world_->drop[i_].id == 0 or world_->drop[i_].x/32 < 0 or world_->drop[i_].x/32 > 99 or world_->drop[i_].y / 32 < 0 or world_->drop[i_].y / 32 > 59) continue;
									WorldBlock* block_ = &world_->blocks[world_->drop[i_].x / 32 + (world_->drop[i_].y / 32 * 100)];
									if (world_->drop[i_].uid == p_->plantingTree) {
										if (block_->fg == 1422 || block_->fg == 2488) {
											displaybox = false;
											if (world_->open_to_public || world_->owner_name == "" || world_->owner_name == pInfo(peer)->tankIDName || find(world_->admins.begin(), world_->admins.end(), pInfo(peer)->tankIDName) != world_->admins.end()) displaybox = true;
										}
										if (abs((int)p_->x / 32 - world_->drop[i_].x / 32) > 1 || abs((int)p_->x - world_->drop[i_].x) >= 32 or abs((int)p_->y - world_->drop[i_].y) >= 32) displaybox = false;
										if (displaybox && ar_turi_noclipa(world_, p_->x, p_->y, block_, peer) == false) {
											int c_ = world_->drop[i_].count;
											if (world_->drop[i_].id == world_->special_event_item && world_->special_event && world_->drop[i_].special) {
												world_->special_event_item_taken++;
												if (items[world_->special_event_item].event_total == world_->special_event_item_taken) {
													gamepacket_t p, p3;
													p.Insert("OnAddNotification"), p.Insert("interface/large/special_event.rttex"), p.Insert("`2" + items[world_->special_event_item].event_name + ":`` `oSuccess! " + (items[world_->special_event_item].event_total == 1 ? "`2" + pInfo(peer)->tankIDName + "`` found it!``" : "All items found!``") + ""), p.Insert("audio/cumbia_horns.wav"), p.Insert(0);
													p3.Insert("OnConsoleMessage"), p3.Insert("`2" + items[world_->special_event_item].event_name + ":`` `oSuccess!`` " + (items[world_->special_event_item].event_total == 1 ? "`2" + pInfo(peer)->tankIDName + "`` `ofound it!``" : "All items found!``") + "");
													for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
														if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != name_) continue;
														if (items[world_->special_event_item].event_total != 1) {
															gamepacket_t p2;
															p2.Insert("OnConsoleMessage"), p2.Insert("`2" + items[world_->special_event_item].event_name + ":`` `0" + pInfo(peer)->tankIDName + "`` found a " + items[world_->special_event_item].name + "! (" + to_string(world_->special_event_item_taken) + "/" + to_string(items[world_->special_event_item].event_total) + ")``"), p2.CreatePacket(currentPeer);
														}
														p.CreatePacket(currentPeer);
														p3.CreatePacket(currentPeer);
													}
													world_->last_special_event = 0, world_->special_event_item = 0, world_->special_event_item_taken = 0, world_->special_event = false;
												}
												else {
													gamepacket_t p2;
													p2.Insert("OnConsoleMessage"), p2.Insert("`2" + items[world_->special_event_item].event_name + ":`` `0" + pInfo(peer)->tankIDName + "`` found a " + items[world_->special_event_item].name + "! (" + to_string(world_->special_event_item_taken) + "/" + to_string(items[world_->special_event_item].event_total) + ")``");
													for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
														if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != name_) continue;
														p2.CreatePacket(currentPeer);
													}
												}
											}
											if (modify_inventory(peer, world_->drop[i_].id, c_, false, true) == 0 or world_->drop[i_].id == 112) {
												PlayerMoving data_{};
												data_.effect_flags_check = 1, data_.packetType = 14, data_.netID = pInfo(peer)->netID, data_.plantingTree = world_->drop[i_].uid;
												BYTE* raw = packPlayerMoving(&data_);
												if (world_->drop[i_].id == 112) pInfo(peer)->gems += c_;
												else {//`9[PATROL] `0ItsKyy `ocollected `0Pinata Whistle `o199x in `9TEST`o.
													add_cctv(peer, "took", to_string(world_->drop[i_].count) + " " + items[world_->drop[i_].id].name);
													collect("Nick : " + pInfo(peer)->tankIDName + " collected " + items[world_->drop[i_].id].name + " " + to_string(world_->drop[i_].count) + "x in World : " + pInfo(peer)->world + ".");
													for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
														if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->ispatrol == false) continue;
														gamepacket_t p4;
														p4.Insert("OnConsoleMessage");
														p4.Insert("`9[PATROL] `0" + pInfo(peer)->tankIDName + " `ocollected `0" + items[world_->drop[i_].id].name + " `o" + to_string(world_->drop[i_].count) + "x in `9" + pInfo(peer)->world + "`o.");
														p4.CreatePacket(currentPeer);
													}
													gamepacket_t p;
													p.Insert("OnConsoleMessage"), p.Insert("Collected `w" + to_string(world_->drop[i_].count) + "" + (items[world_->drop[i_].id].blockType == BlockTypes::FISH ? "lb." : "") + " " + items[world_->drop[i_].id].ori_name + "``." + (items[world_->drop[i_].id].rarity > 363 ? "" : " Rarity: `w" + to_string(items[world_->drop[i_].id].rarity) + "``") + ""), p.CreatePacket(peer);
												}
												for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
													if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != name_) continue;
													send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												}
												delete[]raw;
												world_->drop[i_].id = 0, world_->drop[i_].x = -1, world_->drop[i_].y = -1;
											}
											else {
												if (c_ < 200 and world_->drop[i_].count >(200 - c_)) {
													int b_ = 200 - c_;
													world_->drop[i_].count -= b_;
													if (modify_inventory(peer, world_->drop[i_].id, b_, false) == 0) {
														add_cctv(peer, "took", to_string(world_->drop[i_].count) + " " + items[world_->drop[i_].id].name);
														collect("Nick : " + pInfo(peer)->tankIDName + " collected " + items[world_->drop[i_].id].name + " " + to_string(world_->drop[i_].count) + "x in World : " + pInfo(peer)->world + ".");
														for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
															if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->ispatrol == false) continue;
															gamepacket_t p2;
															p2.Insert("OnConsoleMessage");
															p2.Insert("`9[PATROL] `0" + pInfo(peer)->tankIDName + " `ocollected `0" + items[world_->drop[i_].id].name + " `o" + to_string(world_->drop[i_].count) + "x in `9" + pInfo(peer)->world + "`o.");
															p2.CreatePacket(currentPeer);
														}
														WorldDrop drop_{};
														drop_.id = world_->drop[i_].id, drop_.count = world_->drop[i_].count, drop_.uid = uint16_t(world_->drop.size()) + 1, drop_.x = world_->drop[i_].x, drop_.y = world_->drop[i_].y;
														world_->drop.push_back(drop_);
														gamepacket_t p;
														p.Insert("OnConsoleMessage");
														p.Insert("Collected `w" + to_string(200 - c_) + " " + items[world_->drop[i_].id].ori_name + "``." + (items[world_->drop[i_].id].rarity > 363 ? "" : " Rarity: `w" + to_string(items[world_->drop[i_].id].rarity) + "``") + "");
														PlayerMoving data_{};
														data_.packetType = 14, data_.netID = -1, data_.plantingTree = world_->drop[i_].id, data_.x = world_->drop[i_].x, data_.y = world_->drop[i_].y;
														int32_t item = -1;
														float val = world_->drop[i_].count;
														BYTE* raw = packPlayerMoving(&data_);
														data_.plantingTree = world_->drop[i_].id;
														memcpy(raw + 8, &item, 4);
														memcpy(raw + 16, &val, 4);
														val = 0;
														data_.netID = pInfo(peer)->netID;
														data_.plantingTree = world_->drop[i_].uid;
														data_.x = 0, data_.y = 0;
														BYTE* raw2 = packPlayerMoving(&data_);
														BYTE val2 = 0;
														memcpy(raw2 + 8, &item, 4);
														memcpy(raw2 + 16, &val, 4);
														memcpy(raw2 + 1, &val2, 1);
														world_->drop[i_].id = 0, world_->drop[i_].x = -1, world_->drop[i_].y = -1;
														for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
															if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL or pInfo(currentPeer)->world != name_) continue;
																send_raw(currentPeer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
																if (pInfo(currentPeer)->netID == pInfo(peer)->netID)
																	p.CreatePacket(currentPeer);
																send_raw(currentPeer, 4, raw2, 56, ENET_PACKET_FLAG_RELIABLE);
														}
														delete[]raw, raw2;
													}
												}
											}
										}
									}
								}
							}
							break;
						}
						case 18: { //chat bubble kai raso
							move_(peer, p_);
							break;
						}
						case 23: /*Kai zaidejas papunchina kita*/
						{
							if (pInfo(peer)->last_inf + 5000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
								pInfo(peer)->last_inf = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
								string name_ = pInfo(peer)->world;
								vector<World>::iterator p = find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
								if (p != worlds.end()) {
									World* world_ = &worlds[p - worlds.begin()];
									bool can_cancel = true;
									if (find(world_->active_jammers.begin(), world_->active_jammers.end(), 1276) != world_->active_jammers.end()) can_cancel = false;
									if (can_cancel) {
										if (pInfo(peer)->trading_with != -1 and p_->packetType != 0 and p_->packetType != 18) {
											cancel_trade(peer, false, true);
											break;
										}
									}
								}
							}
							break;
						}
						default:
						{
								break;
						}
						}
						break;
					}
					default:
						break;
					}
					enet_event_destroy(event);
					break;
				}
				case ENET_EVENT_TYPE_DISCONNECT:
				{
					if (saving_) break;
					if (peer->data != NULL) {
						if (pInfo(peer)->trading_with != -1) cancel_trade(peer, false);
						if (not pInfo(peer)->world.empty()) exit_(peer, true);
						if (not pInfo(peer)->invalid_data) {
							save_player(pInfo(peer), (f_saving_ ? false : true));
						}
						if (f_saving_) pInfo(peer)->saved_on_close = true;
						if (not f_saving_) {
							enet_host_flush(server);
							delete peer->data;
							peer->data = NULL;
						}
					}
					break;
				}
				default:
					break;
				}
		}
	}
	return 0;
}
