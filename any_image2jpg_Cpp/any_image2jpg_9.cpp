#include <iostream>
#include <vector>
#include <dirent.h>     // pro praci s adresari
#include <sys/types.h>  // datovy typ DIR
using namespace std;

/*
any_image2jpg
verze 9, pouziva navratovej kod, v prikazu system()
paklize by selhal prevod tak se pri 
pouziti parametru "-delete" nesmaze zdroj !
obcas prevod selze u hodne divokejch nazvu plnejch cinskajch nebo ruskejch unicode znaku
apod. na normalni "bordel" jeste celkem v pohode staci

v konzoli nekdy pise misto cesky diakritiky kraviny ale prevede to pak 
se spravnym nazvem viz. screenshoty
vypada to ze ty znaky jenom neumi spravne zobrazit konzole ale jinak to funguje jak ma

odkaz na download ImageMagick verze pro Windows
https://sdilej.cz/35429517/imagemagick-7.1.1-q16.rar
odkaz na soubor "magick.exe" do systemovy promenny PATH !!!
*/

int nalezeno_1, nalezeno_2, nalezeno_3, aa, bb, cc, dd, d_obr, poc_1=1, poc_2=1;
string pripona, nazev_obrazek, pripona_obrazek, obr, out;
string cesta, cmd_1, cmd_2, znak, ar="";
vector<string> seznamSouboru; // dynamicke pole pro nazvy souboru
vector<string> renames = {""}; // musi bejt takto {""}

// pripony obrazku ktere se buou dale spracovavat
vector <string> pripony = {
".jpeg","JPEG", // musi bejt takto !
".png","PNG",
".bmp",".BMP",
".tif","TIF",
".pcx","PCX",
".tiff","TIFF",
".webp","WEBP",
".gif","GIF"
// sem pridavat dalsi pripony obrazku (nedelat carku za poslednim)
};

int main(int argc, char* argv[]) {

// parametr do promenny (pokud je)
if (argc == 2 ){ // kdyz nejni zadnej parametr, tak je argc = 1
ar = argv[1];
}

// zjisti aktualni pwd
char cwd[PATH_MAX];
if (getcwd(cwd, sizeof(cwd)) != nullptr){
}else{
perror("getcwd() error");
cout<< "chyba PWD"<<endl;
system("pause");
return 1;
}

cesta = cwd;

// otevreni adresare pomoci opendir
DIR* adresar = opendir(cesta.c_str());
if (adresar == nullptr) {
cerr<<"adresar se nepodarilo otevrit: "<<cesta<<endl;
return 1;
}

// struktura pro uchovavani informaci o polozce
struct dirent* polozka;
while ((polozka = readdir(adresar)) != nullptr) {
string nazev = polozka->d_name;

// preskoci polozky "." a ".."
if (nazev == "." || nazev == "..")
continue;

// do pole pridava pouze pripony obrazku (vynechava vse ostatni)
for( aa = 0; aa <= pripony.size() -1; aa++ ) {
pripona = pripony[aa];

nalezeno_1 = nazev.find(pripona);
if (nalezeno_1 == string::npos){
continue;
}

seznamSouboru.push_back(nazev); // prida na konec pole
} // aa
} // while

// uzavreni adresare
closedir(adresar);

// info
cout<<"https://github.com/Pavek-Martin-2"<<endl;
cout<<"any_image2.jpg (C++ verze)"<<endl;

if ( ar == "-delete" ){
cout<<"argv[1] = "<<'"'<<"-delete"<<'"'<<endl;	
}

if (( argc >= 2 ) && (ar != "-delete" )){
cout<<endl<<"pouziti:"<<endl;
cout<<"any_image2jpg -delete"<<endl;
cout<<"bude mazat zdrojove soubory po prevodu na jpg "<<endl;
cout<<"verze 9 pouziva NAVRATOVY KOD tzn. ze pokud je pouzit parametr '-delete'"<<endl;
cout<<"a selhal by prevod nejakeho obrazku do 'jpg' tak se zdrojovy obrazek NESMAZE !"<<endl<<endl;
cout<<"zde je url na stazeni ImageMagick verze pro Windows"<<endl;
cout<<"https://sdilej.cz/35429517/imagemagick-7.1.1-q16.rar"<<endl;
cout<<"odkaz na soubor 'magick.exe' MUSI BYT v systemove prommenne PATH"<<endl;
cout<<"(viz. muj GitHub ucet)"<<endl;
system("pause");
return 1;
}
cout<<endl;

// jsou obrazky v adresari ?
if ( seznamSouboru.size() == 0){
cerr<<"v aktualnim adresari nebyli nenalezeny zadne obrazky"<<endl;
system("pause");
return 1;	
}

// vypis co je v poly souboru obrazku v aktualnim adresari ( diakritika ?? )
for( bb = 0; bb <= seznamSouboru.size() -1; bb++ ) {
obr = seznamSouboru[bb];

// hleda tecku (rozdelovac od kocnce nazvu souboru)
d_obr = obr.length(); // 25 ok

for( cc = 0; cc <= d_obr -1; cc++ ) {
znak = obr[cc];

if (znak == "."){
nalezeno_2 = cc;
}

} // for cc

nazev_obrazek = obr.substr(0, nalezeno_2);
pripona_obrazek = obr.substr( nalezeno_2 + 1, (d_obr - nalezeno_2 - 1));

// rename
nalezeno_3 = 0;
out = "";

for (dd = 0; dd <= renames.size() -1; dd ++) {	
if (nazev_obrazek == renames[dd]){
nalezeno_3++;
}
}

// vyhodnoceni rename
if (nalezeno_3 < 1) {
out += nazev_obrazek;
}else{
out += nazev_obrazek;
out += "(";
out += to_string(nalezeno_3); // int -> string
out += ")";
}

out += ".jpg";
renames.push_back(nazev_obrazek); // prida na konec pole

// magick.exe konverze
// -delete source ?
if ( ar == "-delete" ){
// prevod && mazani ( funguje pri selhani prevodu ze nesmaze zdroj !)
cmd_2 = "magick "; // musi byt v ceste PATH !!
cmd_2 += '"';
cmd_2 += obr;
cmd_2 += '"';
cmd_2 += " "; // jinak to neslo
cmd_2 += '"';
cmd_2 += out;
cmd_2 += '"';
cmd_2 += " && "; // pokud prevod selze pouzije se navratovy kod a zdroj se NESMAZE !
cmd_2 += "del ";
cmd_2 += '"';
cmd_2 += obr;
cmd_2 += '"';
//cout<<cmd_2<<endl;
cout<<poc_2<<") "<<obr<<" --> "<<out<<endl;
cout<<"del "<<'"'<<obr<<'"'<<endl<<endl;
poc_2++;
system(cmd_2.c_str());
}else{
// jen prevod be mazani zdroju
cmd_1 = "magick "; // musi byt v ceste PATH !!
cmd_1 += '"';
cmd_1 += obr;
cmd_1 += '"';
cmd_1 += " "; // jinak to neslo
cmd_1 += '"';
cmd_1 += out;
cmd_1 += '"';

// tisk co zrovna prevani ( unicode nevypisuje spravne ale spravne snim pracuje !)
cout<<poc_1<<") "<<obr<<" --> "<<out<<endl<<endl;
poc_1++;
system(cmd_1.c_str()); // prevede string na const char* !
}

} // for bb

system("pause");
return 0;
}

