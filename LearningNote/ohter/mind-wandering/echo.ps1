ls | Where-Object -FilterScript {$_.Name -like "[7-9]*.md"} |
ForEach-Object {
$Name = $_.Name
$newName = '{0}-{1}' -f "2019", $Name
Rename-Item -Path $_.FullName -NewName $newName
}