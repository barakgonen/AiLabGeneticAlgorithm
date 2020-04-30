param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("string_matching", "nQueens")]
    [string]$commandToExecute=$Args[0],
    [Parameter(Mandatory = $true)]
    [string]$inputString=$Args[1],
    [Parameter(Mandatory = $true)]
    [ValidateSet("default", "BullAndCow")]
    [string]$heuristic = $Args[2],
    [Parameter(Mandatory = $true)]
    [ValidateSet("y", "n")]
    [string]$useRws = $Args[3],
    [Parameter(Mandatory = $true)]
    [ValidateSet("y", "n")]
    [string]$useAging = $Args[4]
)

Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "InputString:" $inputString
Write-Host "Heuristic:" $heuristic
Write-Host "Use-RWS:" $useRws
Write-Host "Use-Aging:" $useAging

$exe = "$pwd/cmake-build-debug/geneticString.exe"
#&$exe $commandToExecute $inputString "default" "y" "y"
#&$exe $commandToExecute $inputString "default" "y" "n"
#&$exe $commandToExecute $inputString "default" "n" "n"
#&$exe $commandToExecute $inputString "default" "n" "y"
#&$exe $commandToExecute $inputString $heuristic "y" "y"
&$exe $commandToExecute $inputString $heuristic "y" "n"
#&$exe $commandToExecute $inputString $heuristic "n" "n"
&$exe $commandToExecute $inputString $heuristic "n" "y"
