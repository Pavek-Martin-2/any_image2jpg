cls

# any_image2jpg_ver-5.ps1

# jestli nasel soubor magick.exe
$magick = ("C:\Program Files (x86)\ImageMagick-7.1.1-Q16\magick.exe")
# tady upravit cestu, podle svoji situace a nebo taky by se dal pozit pripadne Test-Command
if (-not (Test-Path $magick)) {
Write-Warning "nenalezen soubor $magick"
sleep 5
Exit
}


<# zde, druha moznost
$magick ="magick" # magick nekde v ceste PATH !
if (-not (Get-Command $magick -ErrorAction SilentlyContinue )) {
Write-Warning "nenalezen soubor $magick"
sleep 5
exit 1
}
#>

[string] $pwd2 = Get-Location
if ($pwd2.Length -ne 3){
$pwd2+="\"
}

$pripony_obrazku = @("*.png", "*.tif", "*.jpeg", "*.pcx", "*.bmp", "*.gif", "*.tiff", "*.webp")
# co chybi tak jeste doplnit

$pripona_jpg = ".jpg"
$pocitadlo = 1

# pole pro ukladani jiz pouzitych nazvu souboru pri konverzi ( nazvy bez pripon pouze )
$renames = @()

$files = @()
$files += Get-ChildItem -path $pwd2 -Include $pripony_obrazku -Name -File

Write-host -ForegroundColor Green "Imagemagick for Windows, any_image2jpg (verze 5)"
echo ""

$d_files = $files.Length

if ( $d_files -eq 0 ) {
Write-Warning "nenalezen zadne obrazky"
sleep 5
Exit
}

# odzadu v cyklu hledat prvni tecku jako rozdelovac (vice tecek v nazvu)
for ( $cc = 0; $cc -le $d_files -1; $cc++ ) {
$nalezeno = 0
$radek = $files[$cc]

$d_radek = $radek.Length

for ( $dd = $d_radek -1; $dd -ge 0; $dd-- ) {
$znak_radek = $radek[$dd]

if ( $znak_radek -like "." ) {
$nalezeno = $dd
break
}
}

$file_name = $radek.Substring(0,$nalezeno)

$file_pripona = $radek.Substring($nalezeno + 1,$d_radek - $nalezeno - 1 )

[string] $pocitadlo2 = $pocitadlo
$pocitadlo2+=") "

$nasel = 0

for ($bb = 0; $bb -le ($renames.length - 1); $bb ++) {
if ($file_name -like $renames[$bb] ) {
$nasel++
}
}

$source = '"' + $pwd2 + $file_name + "." + $file_pripona + '"'
[string] $nasel2 = $nasel

if ($nasel -lt 1 ){
$target = '"' + $pwd2 + $file_name + $pripona_jpg+ '"'
}else{
$target = '"' + $pwd2 + $file_name + "(" + $nasel2 + ")" + $pripona_jpg + '"'
}

Write-Host -ForegroundColor red $pocitadlo2 -NoNewline
Write-Host -ForegroundColor Yellow $source -NoNewline
Write-Host -ForegroundColor red " --> " -NoNewline
Write-Host -ForegroundColor cyan $target

if ( $args[0] -notlike "-delete" ){
echo ""
}

# provadi prevod
& $magick "$source" "$target"
sleep -Milliseconds 300

# maze stary obrazky
if ( $args[0] -like "-delete" ){
$smaz_source = "$pwd2$radek"
Write-Host -ForegroundColor magenta $smaz_source
Remove-Item -Path $smaz_source
echo ""
sleep -Milliseconds 200
}

# jiz pouziti target nazev prida do pole $renames, pro dalsi kontrolu
# aby se zabranilo duplicitnim nazvum a tim prepisovani souboru
$renames += $file_name

$pocitadlo++
}

Read-Host -Prompt "Press ENTER to continue . . ."
