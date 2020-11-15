$mySchedule = Register-ScheduledJob -Name start_node -ScriptBlock {
    D:\test_selenium\node\renode.ps1
}

Start-Job -Name hub -ScriptBlock {taskkill /f /im java.exe;
cd D:\test_selenium\hub
java -jar selenium-server-standalone-3.141.59.jar -role hub;}

$mySchedule 