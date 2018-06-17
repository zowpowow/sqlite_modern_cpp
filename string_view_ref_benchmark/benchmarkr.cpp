#define PASS_STRING_VIEW_BY_REFERENCE
#include <nonius/nonius.h++>
#include <sqlite_modern_cpp.h>
#include <string_view>
using namespace sqlite;
using namespace std;
const std::string_view Firstnames[] = { "Chase","Mike","Mario","Chase","Gabriel","Hannah","Ora","Cora","Alejandro","Jean","Carrie","Miguel","Don","Maria","Connor","Bruce","Chase","Darrell","Allie","Josie","Andrew","Luke","Theresa","Nelle","Winifred","Sylvia","Melvin","Delia","Joel","Victoria","Connor","Bertie","Cecilia","Iva","Zachary","Dennis","Jesse","Mamie","Ray","Winifred","Gene","Barry","Jeff","Gilbert","Florence","Tyler","Mabel","Alexander","Linnie","Estelle","Micheal","Randall","Nannie","Viola","Christian","Lucinda","Trevor","Virginia","Jennie","Jennie","Flora","Wesley","Madge","Laura","Victor","Lou","Rodney","Rodney","Larry","Barry","Jeffrey","Ollie","Floyd","Oscar","Adam","Tommy","Leonard","Carlos","Allen","Myrtie","Lillian","Verna","Jacob","Verna","Jay","Alfred","Marie","Sophie","Mae","Birdie","Herbert","Julia","Mitchell","Joshua","Estella","Norman","Lelia","Alma","Jackson","Lucinda","Alta","Bill","Elva","Rosetta","Marie","Johnny","Harriet","Harry","Lenora","Alan","Mattie","Estella","Dorothy","Ida","Herbert","Ora","Andre","Belle","Alta","Lucinda","Blake","Leona","Lenora","Christina","Fannie","Callie","Josie","Margaret","Frederick","Trevor","Maria","Essie","Roxie","Mildred","Daniel","Johnny","Billy","Henrietta","Maud","Ian","Theresa","Cody","Viola","Bertha","Henrietta","Amy","Richard","Lizzie","Ann","Christina","Louise","Ruby","Marian","Troy","Allen","Lula","Virgie","Patrick","Alvin","Jeffrey","Herbert","Flora","Scott","Leonard","Susan","Celia","May","Jane","Charlie","Austin","Gertrude","Gerald","Laura","Steve","Jerry","Bertha","Alejandro","Katie","Isabel","Joshua","Johnny","Kevin","Charlotte","Iva","Randy","Andre","Frederick","Lois","Carl","Nannie","Abbie","Rose","Fanny","Eula","Hattie","Estella","Bruce","Mina","Matilda","Kenneth","Emilie","Cornelia","Alfred","Maud","Dennis","Jose","Jeremiah","Jay","Gregory","Loretta","Jerome","Randy","Mable","Sam","Elnora","Nettie","Florence","Jose","Raymond","Jordan","Ora","Trevor","Etta","Blanche","Owen","Lulu","Joe","Mabel","Mabelle","Alfred","Verna","Aiden","Jimmy","Rachel","Fred","Roger","Jeffrey","Fanny","Alfred","Irene","Elsie","Delia","Corey","Marc","Tyler","Antonio","Mittie","Daniel","Noah","Austin","Ethan","Terry","Bradley","Adrian","Tommy","Cameron","Lottie","Keith","David","Eula","Fanny","Sadie","Raymond","Mario","Ruby","Harriett","Polly","Louisa","Edwin","Devin","Christine","Jennie","Micheal","Isaiah","Gary","Lina","Roy","Ida","Theodore","Roy","Mattie","Leon","Todd","Joe","Troy","Cameron","Rebecca","Donald","Tommy","Irene","Verna","Ora","Mabelle","Lee","Mason","Devin","Glen","Clyde","Linnie","Roxie","Chad","Isabelle","Virginia","Bernice","Mamie","Ronnie","Maurice","Ivan","Erik","Edna","Ora","Lora","Brett","Georgie","Esther","Bryan","Lily","Leona","Edna","Flora","Juan","Don","Eunice","Leon","Chase","Virginia","Alvin","Jesus","Micheal","Howard","Jack","Richard","Gabriel","Lelia","Jeremy","Mina","Jayden","Chad","Lettie","Amelia","Lena","Sean","Lucas","Birdie","David","Tyler","Mittie","Violet","Cora","Nora","Landon","Fanny","Ryan","Hallie","Maggie","Lawrence","Olivia","Daisy","Ronnie","Marvin","Sam","Lydia","Ray","Victoria","Lora","Leroy","Floyd","Michael","Logan","Charlotte","Jorge","Violet","Roger","Mark","Steve","Matthew","Florence","John","Melvin","Estella","Cecilia","Ellen","Clarence","Ryan","Inez","Bess","Rosa","Marie","Lillie","Katharine","Katherine","Lenora","Virginia","Lloyd","Betty","Hunter","Zachary","Myrtie","George","Sean","Rebecca","Isabelle","Lucas","Cory","Adrian","Lola","Ricky","Alan","Ida","Peter","Robert","Nina","Alberta","Maurice","Jon","Lilly","Dollie","Victoria","Aiden","Callie","Jim","Adele","Troy","Warren","Ruby","Stella","Rosalie","Dustin","Cecilia","Pearl","Jacob","Jack","Marcus","Leroy","Ivan","Clifford","Grace","Wayne","Fannie","Gilbert","Earl","Jim","Mae","Ruby","Lucinda","Gabriel","Mable","Jeremiah","Sarah","Eliza","Sophie","Marian","Albert","Louisa","Henry","Christian","Alfred","Mayme","Vernon","Agnes","Francis","Cole","Adeline","Jacob","Tommy","Ada","Seth","Bill","Amanda","Winifred","Mildred","Ronald","Isabella","Trevor","Ellen","Bryan","Estelle","Mary","Mabel","Barry","Bertie","Sean","Fannie","Josephine","Daisy","Katherine","Fred","Myrtie","Lloyd","Jesus","Steve","Jesse","Irene","Eva","Phillip","Clara","Gabriel","Helena","Mittie","Lloyd","Francis","Jorge","Violet","Allen","Isaac","Olivia","Pauline","Floyd","Randall","Herman","Louis","Della","Cecelia","Maurice","Mary","Philip","Jayden","Luis","Bettie","Theodore","Ralph","Sue","Emma","Ellen","Miguel","Robert","Pauline","Maud","Owen","Alejandro","Curtis","Samuel","David","Rosalie","Lettie","Hettie","Marc","Violet","Josie","Lee","Violet","Harvey","Owen","Rose","Dominic","Jay","Anne","Ina","Gordon","Gavin","Sarah","Marvin","Tillie","Agnes","Stanley","Jason","Elva","Brent","Ethel","Ann","Henrietta","Wesley","Nellie","Roy","Maude","Gary","Helena","Rodney","Hannah","Victoria","Harriett","Brian","Leona","Delia","Stanley","Virgie","Nicholas","Olive","Charlie","Gavin","Ray","James","Nora","Ruth","Elnora","Eric","Jimmy","Mayme","Charlotte","Rosetta","Teresa","Juan","Ora","Brent","Willie","Eunice","Cornelia","Jean","Curtis","Cynthia" };

NONIUS_BENCHMARK("insert into table then retrieve (const reference)", [] {
	database db(":memory:");
	db << "CREATE TABLE foo (a string);\n";
	for (const auto &a : Firstnames)
	{
		db << "INSERT INTO foo VALUES (?)" << a;
	}
	for (const auto &a : Firstnames)
	{
		db << "SELECT rowid FROM foo WHERE a = ?" << a >> [&a](int x) {
			if (Firstnames[x - 1] != a)
			{
				std::cout << "tableName:" << Firstnames[x - 1] << "refname: " << a;
				throw std::exception("mismatch!");
			}
		};
	}
})

NONIUS_BENCHMARK("insert into table then retrieve w/ prepared statements (const reference)", [] {
	database db(":memory:");
	db << "CREATE TABLE foo (a string);\n";
	auto InsertStatement = db << "INSERT INTO foo VALUES (?)";
	for (const auto &a : Firstnames)
	{
		InsertStatement << a;
		InsertStatement.execute();
	}
	auto SelectStatement = db << "SELECT rowid FROM foo WHERE a = ?";
	for (const auto &a : Firstnames)
	{
		SelectStatement << a;
		SelectStatement >> [&a](int x) {
			if (Firstnames[x - 1] != a)
			{
				std::cout << "tableName:" << Firstnames[x - 1] << "refname: " << a;
				throw std::exception("mismatch!");
			}
		};
	}
})
