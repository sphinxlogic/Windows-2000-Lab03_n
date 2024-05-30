//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
public interface SDKConsts
{
	public static final String IMG_NAMES[] = { 
		"bounce1.gif",	"bounce2.gif",	"bounce3.gif",	"bounce4.gif",
		"bounce5.gif",	"bounce6.gif",	"bounce7.gif",	"bounce8.gif",
		"brojohn.gif",	"sleeping.gif",	"ringbell.gif",	"dingdong.gif",
		"crab.gif",		"ferns.gif",	"sponge.gif",	"teerex.gif",
		"trilobit.gif",	"volcano.gif",	"jelly.gif",	"people.gif",
		"iceberg.gif",	"rodent.gif",	"pteradac.gif",	"world.gif",
		"russian.gif"
	};

	public static final int NUM_BOUNCE = 8;
	public static final int BOUNCE = 0;
	public static final int NURSERY = 8;
	public static final int NUM_VERSES = 8;
	public static final int CRAB = 12;
	public static final int FERN = 13;
	public static final int SPONGE = 14;
	public static final int TEEREX = 15;
	public static final int TRILOBIT = 16;
	public static final int VOLCANO = 17;
	public static final int JELLY = 18;
	public static final int PEOPLE = 19;
	public static final int ICEBERG = 20;
	public static final int RODENT = 21;
	public static final int PTERADAC = 22;
	public static final int WORLD = 23;
	public static final int RUSSIAN = 24;

	public static final int NUM_IMAGES = 25;
	public static final int NUM_IMAGES_HOT = 0;

	public static final int DIR_RIGHT = 1;
	public static final int DIR_LEFT = 2;
	public static final int DIR_UP = 4;
	public static final int DIR_DOWN = 8;

	public static final int BR_RED = 0;
	public static final int LIME = 1;
	public static final int DEEP_BLUE = 2;
	public static final int PURPLE = 3;
	public static final int YELLOW = 4;
	public static final int SKY_BLUE = 5;
	public static final int DK_RED = 6;
	public static final int KHAKI = 7;
	public static final int TEAL = 8;
	public static final int WHITE = 9;
	public static final int PEACH = 10;
	public static final int GR_BLUE = 11;
	public static final int PINK = 12;
	public static final int FOREST_GRN = 13;
	public static final int NUM_COLORS = 14;

	public static final int CLRS[][] = {
		{225,75,0}, {0,225,75}, {75,0,225}, {150,0,150}, {255,255,0}, 
		{0,255,255}, {180,0,80}, {150,150,0}, {0,150,150}, {255,255,255}, 
		{255,127,127}, {127,127,255}, {255,0,127}, {0,127,0}
	};

	public static final String VERSES[] = {
		"Frere Jacques,", "Dormez-vous?", "Sonnez les matines,", "Ding, dang, dong..." };
}

final class GeoROOT implements SDKConsts
{
	public static final String NAME = "Geological Tree";
	public static final String START = "4.6 Billion years ago";
	public static final String END = "Today";
	public static final int IMAGE = WORLD;
}

final class GeoERA implements SDKConsts
{
	public static final String NAME[] = {
		"Precambrian", "Paleozoic", "Mesozoic", "Cenozoic"
	};

	public static final String START[] = {
		"4.6 Billion years ago",
		"570 Million years ago",
		"240 Million years ago",
		"63 Million years ago"
	};

	public static final String END[] = {
		"570 Million years ago",
		"240 Million years ago",
		"63 Million years ago",
		"Today"
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

	public static final String START[][] = {
		{ },
		{	"570 Million years ago", 
			"500 Million years ago",
			"435 Million years ago",
			"410 Million years ago",
			"360 Million years ago",
			"290 Million years ago" },
		{	"240 Million years ago",
			"205 Million years ago",
			"138 Million years ago" },
		{	"63 Million years ago",
			"2.5 Million years ago" }
	};

	public static final String END[][] = {
		{ },
		{	"500 Million years ago", 
			"435 Million years ago",
			"410 Million years ago",
			"360 Million years ago",
			"290 Million years ago",
			"240 Million years ago" },
		{	"205 Million years ago",
			"138 Million years ago",
			"63 Million years ago" },
		{	"2.5 Million years ago",
			"Today" }
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

	public static final String START[][][] = {
		{ {} }, { {} }, { {} },
		{
			{	"63 Million years ago",
				"54 Million years ago",
				"40 Million years ago",
				"25 Million years ago",
				"12 Million years ago" },
			{	"2.5 Million years ago",
				"10,000 years ago" }
		}
	};

	public static final String END[][][] = {
		{ {} }, { {} }, { {} },
		{
			{	"54 Million years ago",
				"40 Million years ago",
				"25 Million years ago",
				"12 Million years ago",
				"2.5 Million years ago" },
			{	"10,000 years ago",
				"Today" }
		}
	};

	public static final int IMAGE[][][] = {
		{ {} }, { {} }, { {} },
		{ { RODENT, SPONGE, JELLY, SPONGE, CRAB }, { ICEBERG, PEOPLE } }
	};
}

