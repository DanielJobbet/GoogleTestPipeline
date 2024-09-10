pipeline {
    agent any // Uses any available agent

    stages {
        stage('Clone Repository') {
            steps {
                // Cloning the GitHub repository containing the source code and Google Tests
                git url: 'https://github.com/DanielJobbet/GoogleTestPipeline.git', branch: 'main' // Replace with your repository URL and branch
            }
        }

        stage('Build') {
            steps {
                // Build the project using MinGW on Windows
                bat '''
                    mkdir build
                    cd build
                    cmake .. -G "MinGW Makefiles"
                    mingw32-make.exe
                '''
            }
        }

        stage('Run Tests') {
            steps {
                // Run the tests and save the output to an HTML file
                bat '''
                    cd build
                    .\\FactorialTest --gtest_output=xml:test_results.xml
                    .\\FactorialTest --gtest_output=html:test_results.html
                '''
            }
        }

        stage('Publish Test Results') {
            steps {
                junit 'build/test_results.xml'
                // Publish the HTML report to Jenkins
                publishHTML([
                    reportDir: "build",
                    reportFiles: "test_results.html",
                    reportName: "Test Results",
                    keepAll: true,
                    alwaysLinkToLastBuild: true,
                    allowMissing: true // Ensure the build fails if the report is missing
                ])
            }
        }
    }

    post {
        always {
            // Archiving artifacts and cleaning workspace
            archiveArtifacts artifacts: '**/build/test_results.*', allowEmptyArchive: true
            cleanWs()
        }
    }
}
