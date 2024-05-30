//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
public interface SDKConsts
{
	public static final String IMG_NAMES[] = { 
		"world_1.gif",	"world_2.gif",	"world_3.gif",	"world_4.gif",
		"world_5.gif",	"world_6.gif",	"world_7.gif",	"world_8.gif",
		"world_9.gif",	"world_10.gif",	"world_11.gif",	"world_12.gif",
		"world_13.gif",	"world_14.gif",	"world_15.gif",	"world_16.gif",
		"crab.gif",		"ferns.gif",	"sponge.gif",	"teerex.gif",
		"trilobit.gif",	"volcano.gif",	"jelly.gif",	"people.gif",
		"iceberg.gif",	"rodent.gif",	"pteradac.gif"
	};

	public static final int WORLD = 0;
	public static final int NUM_WORLDS = 16;
	public static final int CRAB = 16;
	public static final int FERN = 17;
	public static final int SPONGE = 18;
	public static final int TEEREX = 19;
	public static final int TRILOBIT = 20;
	public static final int VOLCANO = 21;
	public static final int JELLY = 22;
	public static final int PEOPLE = 23;
	public static final int ICEBERG = 24;
	public static final int RODENT = 25;
	public static final int PTERADAC = 26;
	public static final int NUM_IMAGES = 27;
	public static final int NUM_IMAGES_HOT = 0;

	public static final int S_CHOICE = 1;
	public static final int S_LIST = 2;
	public static final int S_TREE = 3;

	public static final String FRAME_STR[] = {
		"Africa (1)",
		"Atlantic Ocean",
		"South America",
		"American Continent",
		"American Continent - Pacific Ocean (East)",
		"Pacific Ocean (East)",
		"Pacific Ocean (1)",
		"Pacific Ocean (2)",
		"Pacific Ocean (West) - Australia",
		"Australia - SouthEast Asia (1)",
		"Australia - SouthEast Asia (2)",
		"Asia - Australia",
		"Indian Ocean",
		"East Africa - Asia - Indian Ocean",
		"East Africa",
		"Africa (2)"
	};
}

final class GeoROOT implements SDKConsts
{
	public static final String NAME = "Geological Tree";
	public static final String DURATION = "4.6 Billion years ago to today";
	public static final int IMAGE = WORLD;
}

final class GeoERA implements SDKConsts
{
	public static final String NAME[] = {
		"Precambrian", "Paleozoic", "Mesozoic", "Cenozoic"
	};

	public static final String DURATION[] = {
		"4.6 Billion to 570 Million years ago",
		"570 Million to 240 Million years ago",
		"240 Million to 63 Million years ago",
		"63 Million years ago to today"
	};

	public static final int IMAGE[] = {
		VOLCANO, FERN, TEEREX, PEOPLE
	};
}

final class GeoPERIOD implements SDKConsts
{
	public static final String NAME[][] = {
		{ },
		{ "Cambrian", "Ordovician", "Silurian", "Devonian", "Carboniferous", "Permian" },
		{ "Triassic", "Jurassic", "Cretaceous" },
		{ "Tertiary", "Quaternary" }
	};

	public static final String DURATION[][] = {
		{ },
		{	"570 Million to 500 Million years ago", 
			"500 Million to 435 Million years ago",
			"435 Million to 410 Million years ago",
			"410 Million to 360 Million years ago",
			"360 Million to 290 Million years ago",
			"290 Million to 240 Million years ago" },
		{	"240 Million to 205 Million years ago",
			"205 Million to 138 Million years ago",
			"138 Million to 63 Million years ago" },
		{	"63 Million to 2.5 Million years ago",
			"2.5 Million years ago to today" }
	};

	public static final int IMAGE[][] = {
		{ },
		{ TRILOBIT, SPONGE, JELLY, CRAB, FERN, FERN }, 
		{ RODENT, PTERADAC, TEEREX },
		{ CRAB, PEOPLE }
	};
}

final class GeoEPOCH implements SDKConsts
{
	public static final String NAME[][][] = {
		{ {} }, { {} }, { {} },
		{	
			{ "Paleocene", "Eocene", "Oligocene", "Miocene", "Pliocene" },
			{ "Pleistocene (Ice Age)", "Holocene (Modern Times)" }
		}
	};

	public static final String DURATION[][][] = {
		{ {} }, { {} }, { {} },
		{
			{	"63 Million to 54 Million years ago",
				"54 Million to 40 Million years ago",
				"40 Million to 25 Million years ago",
				"25 Million to 12 Million years ago",
				"12 Million to 2.5 Million years ago" },
			{	"2.5 Million to 10,000 years ago",
				"10,000 years ago to today" }
		}
	};

	public static final int IMAGE[][][] = {
		{ {} }, { {} }, { {} },
		{ { RODENT, SPONGE, JELLY, SPONGE, CRAB }, { ICEBERG, PEOPLE } }
	};
}

