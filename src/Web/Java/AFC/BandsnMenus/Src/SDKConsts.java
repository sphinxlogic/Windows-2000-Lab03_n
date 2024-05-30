//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
public interface SDKConsts
{
	public static final String IMG_NAMES[] = { 
		"earth.gif",	"venus.gif",	"mars.gif"
	};

	public static final int EARTH = 0;
	public static final int VENUS = 1;
	public static final int MARS = 2;
	public static final int NUM_IMAGES = 3;
	public static final int NUM_IMAGES_HOT = 0;

	public static final int ID_BASE = 550;
	public static final int ID_VENUS = ID_BASE + 0;
	public static final int ID_EARTH = ID_BASE + 1;
	public static final int ID_MARS = ID_BASE + 2;
	public static final int PRECAMBRIAN = ID_BASE + 3;
	public static final int CAMBRIAN = ID_BASE + 4;
	public static final int ORDOVICIAN = ID_BASE + 5;
	public static final int SILURIAN = ID_BASE + 6;
	public static final int DEVONIAN = ID_BASE + 7;
	public static final int CARBONIFEROUS = ID_BASE + 8;
	public static final int PERMIAN = ID_BASE + 9;
	public static final int TRIASSIC = ID_BASE + 10;
	public static final int JURASSIC = ID_BASE + 11;
	public static final int CRETACEOUS = ID_BASE + 12;
	public static final int PALEOCENE = ID_BASE + 13;
	public static final int EOCENE = ID_BASE + 14;
	public static final int OLIGOCENE = ID_BASE + 15;
	public static final int MIOCENE = ID_BASE + 16;
	public static final int PLIOCENE = ID_BASE + 17;
	public static final int PLEISTOCENE = ID_BASE + 18;
	public static final int HOLOCENE = ID_BASE + 19;
	public static final int NUM_INFO = 20;

	public static final String INFO[] = {
"Planet Venus\n\n    One of nine planets in the solar system, the second " +
"in distance from the sun. Except for the sun and the moon, Venus " +
"is the brightest object in the sky. The planet is called the morning " +
"star when it appears in the east at sunrise, and the evening star when " +
"it is in the west at sunset. In ancient times the evening star was " +
"called Hesperus and the morning star Phosphorus or Lucifer. Because " +
"of the distances of the orbits of Venus and earth from the sun, Venus " +
"is never visible more than three hours before sunrise or three hours " +
"after sunset.\n\n" +
"    When viewed through a telescope, the planet exhibits phases like " +
"the moon. Full Venus appears the smallest because it is on the far " +
"side of the sun from earth. Maximum brilliance (a stellar magnitude " +
"of -4.4, or 15 times the brightest star) is seen in the crescent " +
"phase. The phases and positions of Venus in the sky repeat with the " +
"synodic period of 1.6 years. Transits across the " +
"face of the sun are rare, occurring in pairs at intervals of a " +
"little more than a century. The next two will be in 2004 and 2012.",

"Planet Earth\n\n    One of nine planets in the solar system, the third in distance " +
"from the sun and the fifth largest of the planets in diameter. The " +
"mean distance of the earth from the sun is 149,503,000 km (92,897,000 mi). " +
"It is the only planet known to support life, although some of the " +
"other planets have atmospheres and contain water.\n\n" +
"    The earth is not a perfect sphere but is slightly oblate, or " +
"flattened at the poles. The diameter of the earth measured around " +
"the North Pole and the South Pole is about 42 km (26 mi) less than " +
"the diameter of the earth measured at the equator.",

"Planet Mars\n\n    One of nine planets in the solar system, it is the fourth " +
"planet from the sun and orbits the sun at a distance of about 228 million " +
"km (about 141 million mi). Mars is named for the Roman god of war because " +
"it appears fiery red in the earth's night sky.\n\n" +
"    Mars is a relatively small planet, with about half the diameter of Earth " +
"and about one-tenth Earth's mass. The force of gravity on the surface of " +
"Mars is about one-third of that on Earth. Mars has twice the diameter and " +
"twice the surface gravity of Earth's moon. The surface area of Mars is " +
"almost exactly the same as the surface area of the dry land on Earth.\n\n" +
"    The Martian day, or the time it takes Mars to rotate once on its axis, is " +
"about a half an hour longer than an Earth day. Its year, or the time it " +
"takes to revolve once around the sun, is about two Earth years long. Mars " +
"has two moons, Phobos and Deimos, which are named after the dogs of the " +
"Roman god Mars. These tiny bodies are heavily cratered dark chunks of rock " +
"and may be asteroids captured by the gravitational pull of Mars. Phobos " +
"orbits Mars once in less than one Martian day, so it appears to rise in " +
"the west and set in the east, usually twice each day. Deimos has the more " +
"ordinary habit of rising in the east and setting in the west.",

"Precambrian Era\n\n" +
"    The span of time starting at the beginning of geologic history, " +
"when rocks first formed, and extending to the beginning of the Cambrian Period, " +
"when multicellular life first became abundant. The Precambrian began about four " +
"billion years before the present time and ended about 570 million years ago. The " +
"earth's oldest known rocks have been dated at 4.03 billion years old. Precambrian " +
"rocks have been found in Canada, Scandinavia, Africa, Brazil, Western Australia, " +
"and East Antarctica.\n\n" +
"    Although the earth has been determined to be 4.6 billion years old, evidence " +
"of the first 600 million years of the earth's history has not yet been found in " +
"the rock record. Even the geologic record of the Precambrian, written in the " +
"surviving rocks, is sparse. Earth scientists must use the rock record that has " +
"been preserved to hypothesize and form theories about earth's origin.\n\n" +
"    During the Precambrian, continents began to form and grow, driven by a " +
"mechanism similar to what is now called plate tectonics. Also during this time, " +
"the oceans and the atmosphere started forming from the gases escaping the " +
"extremely hot, semiliquid interior of the earth. Life in the form of primitive " +
"bacteria may have originated as early as four billion years ago, perhaps at " +
"hot springs on the sea floor.",

"Cambrian Period\n\n" +
"    First division of the Paleozoic era, spanning an interval of about 70 million years, " +
"from 570 to 500 million years ago. It was named in 1835 by the English geologist Adam " +
"Sedgwick for sedimentary rocks in Wales, which the ancient Romans knew as Cambria.\n\n" +
"    By the dawn of the Paleozoic era, the steadily increasing oxygen content of the " +
"atmosphere and oceans had made it possible for the marine environment to support " +
"new forms of life. Thus, for the first time in the history of the earth, " +
"creatures evolved that could derive energy from respiration. The earliest of " +
"these new organisms were relatively large, complex marine invertebrates. With " +
"hard shells and skeletons of chitin or lime, these creatures had far better " +
"chances of preservation in the fossil record than the soft-bodied life of " +
"the Precambrian time. Of the latter, only sparse carbonized remains are found.",

"Ordovician Period\n\n" +
"    Second division of the Paleozoic era, spanning a period from about 500 million " +
"to 435 million years ago. It was named for an ancient Welsh tribe, rocks of this " +
"age having first been studied systematically in Wales.\n\n" +
"    North America and " +
"Europe, separated by water during the preceding Cambrian period, collided " +
"in Ordovician time, crumpling between them a great thickness of accumulating " +
"sediments of the Appalachian geosyncline and lifting these rocks to form a " +
"mountain range, the Taconics, remnants of which are visible today in eastern " +
"New York State.\n\n" +
"    Marine invertebrates were still the predominant life forms. On land, a few forms " +
"of primitive life may have appeared - plants and burrowing invertebrates similar " +
"to millipedes. The seas now harbored the earliest vertebrates, primitive fish with " +
"bony armor plates. Graptolites (extinct colonial organisms), corals, crinoids, " +
"bryozoans, and clams first made their appearance in this period.",

"Silurian Period\n\n" +
"    The third division of the Paleozoic era, spanning an interval of 25 million years, " +
"from about 435 million to 410 million years ago. It was named in 1835 by the " +
"English geologist Sir Roderick Impey Murchison for an early Brittanic tribe, the " +
"Silures, who inhabited the region of western England and Wales where sedimentary " +
"rocks of this age were first studied systematically.\n\n" + 
"    The Silurian is bracketed " +
"in time by two major mountain-building episodes: the Taconian orogeny of the " +
"preceding Ordovician period, and the Acadian orogeny of the following Devonian.\n\n" +
"    Rocks of Silurian age yield the earliest incontestable remains of terrestrial " +
"vegetation: fossils of a group of extinct, primitive, leafless vascular " +
"plants called psilophytes, characterized by a horizontal stalk that grew " +
"beneath the ground and sent up short, vertical stems. Animal life, mainly " +
"invertebrate and marine, included the first fish with jaws as well as the " +
"first terrestrial insects.",

"Devonian Period\n\n" +
"    The fourth division of the Paleozoic era, spanning an interval from about 410 " +
"million to 360 million years ago, and named for Devonshire, England, where " +
"the sedimentary rocks of that period were first studied in the 1830s. " +
"North America and Europe both straddled the equator at this time.\n\n" +
"    With a newly formed atmospheric ozone layer for protection from deadly ultraviolet " +
"radiation, the first air-breathing arthropods - spiders and mites - appeared " +
"on dry land. In the seas, coiled shellfish called ammonoids (distantly related " +
"to modern squid) were the major form of invertebrate life. Devonian fish, " +
"considerably evolved from the armor-plated types of the preceding Ordovician " +
"period, now had fins and scales as well as jaws. One group, the lobe-fins, gave " +
"rise to the first air-breathing vertebrates - the amphibians - which invaded " +
"the land at the close of Devonian time and set the stage for the advent of the " +
"reptiles in the Carboniferous period that followed.",

"Carboniferous Period\n\n" +
"    The fifth division of the Paleozoic era, spanning a time interval of from " +
"360 to 290 million years ago. The name originated in Great Britain, where it was " +
"first applied, in 1822, to the coal-bearing strata of England and Wales.\n\n" +
"    Animal and vegetable remains are abundant from the Carboniferous period and " +
"are, in many cases, well preserved. Great uniformity is observed in the character " +
"of plant life, the same genera and often the same species being found in widely " +
"separated regions. About 2000 species are known, most of which belong to the " +
"flowerless, spore-producing plants. Early club mosses, horsetails, and forest trees " +
"(Cordaites) were common, in addition to numerous ferns.\n\n" +
"    The contemporary land fauna " +
"left few traces, but the fauna of seas and lagoons are much better represented. " +
"The first true reptiles began to appear, developing from the earlier amphibians. " +
"Corals, crinoids, and minute foraminifers were abundant. A few trilobites and " +
"eurypterids were to be found. Snails and mollusks, including cephalopods and " +
"nautiloids, were widespread. Insects were frequent, particularly a giant form " +
"of dragonfly. Polyzoa and brachiopods were common, and sharks and primitive, " +
"hard-scaled fish were well represented.",

"Permian Period\n\n" +
"    The last division of the Paleozoic era, spanning an interval of 50 million " +
"years, from 290 million to 240 million years ago. The period was named in " +
"1841 by the English geologist Sir Roderick Impey Murchison for a village in " +
"eastern Russia where sedimentary strata of this age were correlated, on the " +
"basis of fossil content, with strata farther west in Germany.\n\n" +
"    The invertebrate marine life of the beginning of the period was exceptionally " +
"rich, flourishing in the warm, shallow inland seas. Toward the end of the period, " +
"a wave of mass extinctions, the greatest in all earth history, brought to an end " +
"large groups of corals, bryozoans, echinoderms, and other invertebrates. On land, " +
"seed ferns were joined by conifers and ginkgoes. Amphibians were declining in number, " +
"but reptiles, which had appeared in the preceding period, were undergoing a " +
"spectacular evolutionary development of carnivorous and herbivorous, mammal-like " +
"forms. Also during the Permian period the forerunners of the dinosaurs appeared.",

"Triassic Period\n\n" +
"    The first of the three divisions of the Mesozoic era, spanning an interval of " +
"35 million years, from 240 to 205 million years ago.\n\n" +
"    Fossils found in Triassic strata indicate that the general climate was warm at " +
"that time. Much of North America lay between the equator and 30° North latitude, " +
"so that subtropical conditions existed as far north as Wyoming and New England.\n\n" +
"    The terrain of Triassic times was dominated by evergreen trees, most of them " +
"conifers and ginkgoes. The cycad palms and scale trees that were the most prominent " +
"flora of the preceding period still existed, but were not as numerous or varied " +
"as the evergreens.\n\n" +
"    The most important animals to make their appearance in the " +
"Triassic were the dinosaurs. The earliest members of this group " +
"did not attain the huge dimensions of the dinosaurs of later Mesozoic times and " +
"were for the most part no more than 3 to 4.5 m (10 to 15 ft) long. Other " +
"important reptilians of the Triassic were the ichthyosaurs marine reptiles with " +
"long snouts and with bodies shaped like those of modern dolphins. Other " +
"marine reptiles of the period, the plesiosaurs, had broad, turtlelike bodies, " +
"long necks and tails, and large flippers.\n\n" + 
"    The Triassic period is considered " +
"by many paleontologists to mark the emergence of the first true mammals, but " +
"little is known of their physiology. Among the invertebrates, insects were " +
"represented in the Triassic by the first species to undergo complete " +
"metamorphosis from larva through pupa to adult. In the Triassic seas, " +
"where squidlike belemnites, ammonites, and crustaceans flourished, 75 percent " +
"of invertebrate species were obliterated by a mass extinction.",

"Jurassic Period\n\n" +
"    The second division of the Mesozoic era, extending over a period from roughly " +
"205 to 138 million years ago. The period is named for rock strata from the Jura " +
"Mountains. Toward the end of the Jurassic, these shallow seas began to drain away, " +
"leaving behind thick limestone deposits in which some of the world's richest " +
"accumulations of oil and gas would form.\n\n" + 
"    That the Jurassic climate was warm as " +
"well as moist is shown by widespread coral reefs and by temperate and subtropical " +
"forests consisting largely of the gymnosperms (cycads and conifers), ginkgoes, " +
"and seed ferns. Angiosperms (flowering plants) first appeared in mid-Jurassic " +
"time. Reptiles were the dominant form of animal life. Some had adapted to life " +
"in the sea (ichthyosaurs and plesiosaurs) and the air (pterosaurs) as well as " +
"on land, where a variety of forms developed, some of which reached huge sizes " +
"(the carnivorous Allosaurus and herbivorous Apatosaurus). In 1822 Jurassic " +
"strata in Sussex, England, yielded the bones of one of the first dinosaurs " +
"to be discovered, Iguanodon. Fossil remains of the oldest known bird, the " +
"toothed Archaeopteryx, were also found in rocks of Jurassic age. Mammals, " +
"which had evolved at the end of the preceding Triassic, remained small and " +
"rodentlike for as long as the dinosaurs flourished, throughout the Jurassic.",

"Cretaceous Period\n\n" +
"    The last period of the Mesozoic era, lasting from about 138 million to about " +
"63 million years ago. The name alludes to the abundance of chalk (Latin creta) " +
"strata deposited during the latter part of the period in England " +
"and France and now exposed at sites such as Dover. During the Late Cretaceous, " +
"sea levels rose worldwide, drowning about one-third of the earth's present land " +
"area. Thus heat from the sun could be distributed farther poleward by ocean " +
"currents, producing a warm, mild global climate with ice-free poles and Arctic " +
"water temperatures of 14° C (58° F) or higher.\n\n" + 
"    In such a climate, cold-blooded " +
"reptiles could exist even in northern latitudes, and fossil ferns and cycads found " +
"in Cretaceous rocks at Arctic latitudes are similar to plants growing today in " +
"subtropical rain forests. By Late Cretaceous time the flora had taken " +
"on a modern appearance and included many of today's genera of trees, such as the " +
"oak, beech, and maple. Despite these mild conditions, several mass faunal " +
"extinctions occurred toward the end of the period. Five great reptilian groups " +
"dinosaurs, pterosaurs, ichthyosaurs, plesiosaurs, and mosasaurs that had been " +
"dominant became extinct. A recent theory is that a comet or small asteroid " +
"colliding with earth 63 million years ago blasted enough dust into the atmosphere " +
"to reduce incoming solar radiation and temperatures worldwide, devastating the " +
"algae, vegetation, and small animals on which the large reptiles depended for food.",

"Paleocene Epoch\n\n" +
"    First and shortest of the five divisions of the Tertiary period of the " +
"Cenozoic era, spanning an interval from about 63 million to 54 million " +
"years ago, and originally defined, as were the epochs that followed it, " +
"on the basis of the percentage of modern species of shellfish found in the " +
"fossil record.\n\n" +
"    The dinosaurs having disappeared at the end of the preceding " +
"Cretaceous period, mammalian life now began to dominate the earth. Chief " +
"among the early mammals were marsupials, insectivores, lemuroids, creodonts " +
"(the carnivorous stock ancestral to all cats and dogs), and primitive hoofed " +
"animals from which such diverse groups as the horses, rhinoceroses, pigs, " +
"and camels were to evolve in later years.",

"Eocene Epoch\n\n" +
"    The second division of the Cenozoic era, spanning an interval from about " +
"54 to 40 million years ago. Like the Paleocene epoch, which preceded it, " +
"and the Oligocene, which followed it, the Eocene was originally defined " +
"in the 19th century by the British geologist Sir Charles Lyell on the " +
"basis of the percentage of modern species of shellfish found in Cenozoic " +
"rock strata.\n\n" +
"    The climate of Eocene times was subtropical and moist throughout North " +
"America and Europe. In the U.S., palm trees and alligators lived as far " +
"north as the Dakotas, while at high northern latitudes in Greenland and " +
"Siberia, moist Temperate Zone forests were dominated by giant redwoods and " +
"deciduous trees such as beech, chestnut, and elm. In Alaska's warm Eocene " +
"climate, cycads, magnolias, and fig trees flourished.\n\n" + 
"    The rapid evolution " +
"of new orders of mammal life continued from the preceding Paleocene. " +
"Ancestral forms of the horse, rhinoceros, camel, and other modern groups " +
"such as bats, primates, and squirrel-like rodents appeared simultaneously in " +
"Europe and North America. Many were strikingly small compared with today's " +
"forms. The earliest horse was barely 30 cm (12 in) high, with three toes " +
"on its hind feet and four on its front feet. The carnivores of the time, " +
"called creodonts, were the stock from which modern dogs and cats would later " +
"evolve.\n\n" + 
"    The latter part of the epoch witnessed the first adaptation of " +
"mammals to life in the sea. Fossil bones of an Eocene whalelike animal " +
"are found in the southern U.S., Egypt, and Europe. The largest of these " +
"animals was more than 15 m (more than 50 ft) long, but not so large that " +
"it could not be preyed upon by the sharks of the time, some species of " +
"which had jaws as wide as 1.8 m (6 ft) across.",

"Oligocene Epoch\n\n" +
"    Third division of the Tertiary period of the Cenozoic era, spanning an " +
"interval from about 40 to 25 million years ago. Like the Eocene epoch, " +
"which preceded it, and the Miocene, which followed, the Oligocene " +
"was originally defined by the percentage of modern species of shellfish " +
"(10-15 percent) found in strata of this age.\n\n" +
"    Mammals were firmly established in the Oligocene as the dominant form of " +
"terrestrial life. The horse, a native of North America, continued to evolve " +
"there. Meanwhile vast herds of oreodons (piglike cousins of the camel) " +
"grazed across the plains of North America, as did the " +
"enteledonts (even-toed, giant pigs) that were also native to that " +
"continent; both groups became extinct in the Miocene. The first elephants " +
"gave rise, in Africa, to the mastodons, which were as yet only a little more " +
"than 1.5 m (5 ft) high. Creodonts had by then diverged to form the dogs and cats; " +
"the latter comprised two groups, from one of which the saber-toothed cats " +
"developed. Rodents were well represented by this time, and primates included " +
"the tarsiers and lemurs. Finally, Oligocene strata have yielded bones of the " +
"first Old World monkeys, as well as a single species of great ape.",

"Miocene Epoch\n\n" +
"    Fourth division of the Tertiary period of the Cenozoic era, spanning a " +
"time interval from 25 to 12 million years ago.\n\n" +
"    The climate of the Miocene was cooler than that of the preceding epoch. " +
"A circumglobal system of ocean currents had become established in the southern " +
"hemisphere, cutting Antarctica off from the warmer currents of the rest " +
"of the world. This fostered the growth of a great Antarctic ice sheet.\n\n" +
"    In the northern hemisphere, large areas that had formerly been " +
"covered with thick forests became grassy prairies. The fauna of the " +
"Miocene included a number of mammals, among them the rhinoceros, camel, cat, " +
"and horse. The mastodon made its appearance at this time, as did the " +
"raccoon and weasel.\n\n" +
"    During this epoch, large apes, related to the " +
"orangutan, lived in Asia and the southern portion of Europe; these " +
"apes are the closest Miocene relatives of humanlike apes, which first " +
"appeared during the Pliocene epoch.",

"Pliocene Epoch\n\n" +
"    Fifth and most recent division of the Tertiary period of the Cenozoic era, " +
"spanning an interval from about 12 million to 2.5 million years ago.\n\n" +
"    Like the Miocene, which preceded it, the Pliocene was named and defined by " +
"the British geologist Sir Charles Lyell on the basis of the percentage of " +
"modern species of shellfish found in the fossil record.\n\n" +
"    Mammals had long " +
"since established themselves as the dominant terrestrial life form, and " +
"the rapid evolution of one group, the primates, produced species " +
"considered direct ancestors of Homo sapiens.",

"Pleistocene Epoch\n\n" +
"    The Pleistocene, named by the British geologist Charles Lyell in 1839, " +
"immediately follows the Pliocene epoch, " +
"extending from the beginning of the Quaternary period " +
"(2.5 million years ago) to about 10,000 years ago.\n\n" +
"    The Pleistocene was most notably characterized by the spreading of glacier ice " +
"over more than one-fourth of the land surface of the " +
"earth. The flora and fauna of the time, which existed in the regions not " +
"covered by ice, were essentially the same as those of the earlier " +
"Pliocene epoch.\n\n" +
"    By the end of the Pleistocene, however, many species " +
"of mammals had become extinct in North America, including " +
"the llama, camel, tapir, horse, and yak. Other large mammals, such as " +
"the mastodon, saber-toothed tiger, and ground sloth, became " +
"extinct everywhere. While snow and ice accumulated in higher latitudes, " +
"rainfall increased in the lower latitudes, allowing plant and " +
"animal life to flourish in areas of northern and eastern Africa that " +
"have since become arid and barren. Evidence has been found that " +
"the Sahara was occupied by nomadic hunters, as well as by giraffes and " +
"other grazing animals, during the latter part of the Pleistocene.",

"Holocene Epoch\n\n" +
"    During the Recent epoch, beginning about 10,000 years ago, melting ice " +
"caused the sea level to rise a hundred feet or more, " +
"drowning large areas of land and broadening the continental shelf of " +
"eastern North America."};
}

final class GeoERA implements SDKConsts
{
	public static final String NAME[] = {
		"Precambrian", "Paleozoic", "Mesozoic", "Cenozoic"
	};

	public static final int ID[] = { PRECAMBRIAN, 0, 0, 0 };
}

final class GeoPERIOD implements SDKConsts
{
	public static final String NAME[][] = {
		{ },
		{ "Cambrian", "Ordovician", "Silurian", "Devonian", "Carboniferous", "Permian" },
		{ "Triassic", "Jurassic", "Cretaceous" },
		{ "Tertiary", "Quaternary" }
	};

	public static final int ID[][] = {
		{ },
		{ CAMBRIAN, ORDOVICIAN, SILURIAN, DEVONIAN, CARBONIFEROUS, PERMIAN },
		{ TRIASSIC, JURASSIC, CRETACEOUS },
		{ 0,0 }
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

	public static final int ID[][][] = {
		{ {} }, { {} }, { {} },
		{	
			{ PALEOCENE, EOCENE, OLIGOCENE, MIOCENE, PLIOCENE },
			{ PLEISTOCENE, HOLOCENE }
		}
	};
}

