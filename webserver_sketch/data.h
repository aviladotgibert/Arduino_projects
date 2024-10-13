
const char* ssid_1     = "UniversalService";
const char* password_1 = "Service@VLC24";
const char* ssid_2     = "Subcribanse";
const char* password_2 = "alswnet";

const String Pagina =  R"====(HTTP/1.1 200 OK
Content-Type: text/html

//
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Gráfico de Líneas de Temperatura y Humedad</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin: 20px;
        }

        #csvFileInput {
            margin-bottom: 20px;
        }

        canvas {
            max-width: 100%;
            height: auto;
        }
    </style>
</head>
<body>
    <h1>Gráfico de Líneas de Temperatura y Humedad</h1>
    <input type="file" id="csvFileInput" accept=".csv">
    <canvas id="lineChart"></canvas>

    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <script>
        document.getElementById('csvFileInput').addEventListener('change', handleFileSelect);

        function handleFileSelect(event) {
            const file = event.target.files[0];
            if (file && file.type === 'text/csv') {
                const reader = new FileReader();
                reader.onload = function(e) {
                    const csvData = e.target.result;
                    const parsedData = parseCSV(csvData);
                    createLineChart(parsedData);
                };
                reader.readAsText(file);
            } else {
                alert('Por favor, selecciona un archivo CSV.');
            }
        }

        function parseCSV(data) {
            const lines = data.split('\n');
            const labels = [];
            const temperatureData = [];
            const humidityData = [];

            lines.forEach((line, index) => {
                if (index === 0) return; // Omitir la primera línea si contiene encabezados
                const [label, temperature, humidity] = line.split(',');
                if (label && temperature && humidity) {
                    labels.push(label);
                    temperatureData.push(parseFloat(temperature));
                    humidityData.push(parseFloat(humidity));
                }
            });

            return { labels, temperatureData, humidityData };
        }

        function createLineChart(data) {
            const ctx = document.getElementById('lineChart').getContext('2d');
            new Chart(ctx, {
                type: 'line',
                data: {
                    labels: data.labels,
                    datasets: [
                        {
                            label: 'Temperatura',
                            //data: data.temperatureData,
                            data: data.temperatureData,
                            borderColor: 'rgba(255, 99, 132, 1)',
                            backgroundColor: 'rgba(255, 99, 132, 0.2)',
                            fill: false
                        },
                        {
                            label: 'Humedad',
                            data: data.humidityData,
                            borderColor: 'rgba(54, 162, 235, 1)',
                            backgroundColor: 'rgba(54, 162, 235, 0.2)',
                            fill: false
                        }
                    ]
                },
                options: {
                    responsive: true,
                    scales: {
                        x: {
                            title: {
                                display: true,
                                text: 'Fecha'
                            }
                        },
                        y: {
                            title: {
                                display: true,
                                text: 'Valor',
                            }
                        }
                    }
                }
            });
        }
    </script>
</body>
</html>

)====";
