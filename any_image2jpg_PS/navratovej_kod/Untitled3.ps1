cls
$q = "magick "
echo $q

$s = '"' + "TRITON2.gif" + '"' # spatnej
#$s = '"' + "TRITON2.png" + '"' # dobrej
echo $s

$t = '"' + "TRITON2.jpg" + '"'
echo $t

& $q $s $t

$x = $? # navartovej kod prikazu magick do $x (Boolean) funguje jak ma
echo $x
#echo $x.GetTypeCode() # Boolean

if ( $x -like "True"){
echo "smazat zdroj"
#Remove-Item ... 
}else{
echo "CHYBA PREVODU"
}

sleep 30

<#
takova zajimavost, soubor "TRITON2.GIF" to je obrazek z cd-romu, kterej se tady se tady dal kdysi
kopit ve specialnim PC krame jako jedno z prvnich cd-romu , myslim ze se jmenoval "Vrtulnik 1"
pak bylo jeste cd-cko ktery se jmenovalo "Kolotoè", toho bylo vic dilu 1,2,3 myslim a ten Vrtulnik
potom taky
da se to stahnou nekde na "internet archive.org" jako iso, zada se tam do vyhledavani 
"vrtulnik" nebo "kolotoc" nebo "mediatrade" pak byly jeste "Super Hry" a "Winarna", to bylo pro Windows 3.11
a cd-rom "Cervena lucerna" 1,2,3 tu sem tam ale nenasel, po ti se zem slehla :(
myslim ze od nejaky firmy "Madia Trade" to bylo, neco takoviho bylo z boku toho cd-rom
tak tohle kdyby nekdo mel originalky, tak si myslim ze to sou dneska uz docela ceny
sberatelsky kousky tohle je tak asi zacatek 90-tejch let, zhruba
#>
