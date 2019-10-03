#pragma once
//Copyright held by Artemxx and Nikita Sechko

#include <chrono>
#include <random>
#include <vector>

namespace Constants {
	const std::vector<std::string> People{
		"AlexJokel",
		"sanya_saske",
		"asciimowa",
		"vitonka",
		"Mieszok",
		"LamaMarine",
		"Tranvick",
		"Renkens",
		"Nikitaboz",
		"Fedya_1",
		"Vrevt",
		"likynushka",
		"tsm_x",
		"artemxx",
		"Nicksechko",
		"kokhnovich",
		"nenartovich",
		"Am6erman",
		"sashhrmz",
		"vanyakhodor",
		"Alexthundr",
		"Sergey Chernov",
		"katya1512",
		"yanina_tyan",
		"RacctaR",
		"kernalex256",
		"Andrey Naradzetsky",
		"JekaGANG",
		"Sha_Andrey",
		"al_taraikovich",
		"katewonder",
		"Rain_must_fall",
		"Sigismundych",
		"atolstikov",
		"Pavel Metluk",
		"Andrew Nevero",
		"newUsername1",
		"serge_yaskevich",
		"Evgeni Zhibrik",
		"Alexey Vorobiov",
		"Andrew Moisa",
		"Andrei Ilyin",
		"Anime",
		"228"
	};
	static std::mt19937 rnd(std::chrono::steady_clock::
		now().time_since_epoch().count());
	static std::uniform_int_distribution<int> gen(0, People.size() - 1);

	static std::string GetRandomPeople() {
		return People[gen(rnd)];
	}
}
