# Configura el puerto serie
$port = new-Object System.IO.Ports.SerialPort COM3,115200,None,8,one
$port.open()

# Abre el archivo para escribir
$filePath = "C:\Users\david\Documents\Arduino\Proyectos\output.csv"
$streamWriter = [System.IO.StreamWriter]::new($filePath, $true)
#Crea la primera linea
$streamWriter.WriteLine("Fecha,Temperatura,Humedad")

try {
    while ($true) {
        # Lee los datos del puerto serie
		$line = $port.ReadLine()
				
		# Muestra los datos en la consola (opcional)
        Write-Host $line  
        
        # Escribe los datos en el archivo
		$currentDateTime = Get-Date -format "yyyy-mm-dd-HH:mm:ss"
		echo $currentDateTime
		#Escribe la fecha actual más la temperatura y humedad separadas por comas
		$csvformat = $currentDateTime + "," + $line
			#$streamWriter.WriteLine($currentDateTime)
			#$streamWriter.WriteLine($line)
			
		#Comprueba que los datos no estan vacíos
        
		$streamWriter.WriteLine($csvformat) 
        $streamWriter.Flush()
    }
}
catch {
    Write-Host "Se ha producido un error: $_"
}

finally {
    # Cierra el archivo y el puerto serie
    $streamWriter.Close()
    $port.Close()
}
