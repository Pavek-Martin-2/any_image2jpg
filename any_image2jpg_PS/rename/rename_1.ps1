cls

# resi duplicitni nazvy souboru

#$nazvy = @("a","b","c","d","e","f")
$nazvy = @("a","a","a","d","e","f","f","g","g","g")
#$nazvy = @("a","b","c","d","d","f","f1","f1")

$renames = @()

for ( $aa = 0; $aa -le $nazvy.Length -1; $aa++ ) {
$nasel = 0
$file_name = $nazvy[$aa]
                   
for ($bb = 0; $bb -le ($renames.length - 1); $bb ++) {
if ($file_name -like $renames[$bb] ) {
$nasel++
}
}

if ($nasel -lt 1 ){
echo $file_name
}else{
echo "$file_name($nasel)"
}

$renames += $file_name
Write-Host -ForegroundColor cyan $renames
}

Write-Host -ForegroundColor Yellow $renames
sleep 10
