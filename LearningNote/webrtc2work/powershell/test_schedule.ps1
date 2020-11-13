$mySchedule = Register-ScheduledJob -Name start_node -ScriptBlock {
    D:\test_selenium\node\renode.ps1
}