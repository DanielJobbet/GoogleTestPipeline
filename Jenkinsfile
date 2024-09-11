pipeline {
    agent any // Uses any available agent

    stages {
        // stage('Clone Repository') {
        //     steps {
        //         // Cloning the GitHub repository containing the source code and Google Tests
        //         git url: 'https://github.com/DanielJobbet/GoogleTestPipeline.git', branch: 'main'
        //     }
        // }

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
                // Run the tests and save the output to an XML file
                bat '''
                    cd build
                    .\\FactorialTest --gtest_output=xml:test_results.xml
                '''
            }
        }

        stage('Publish Test Results') {
            steps {
                // Publish the XML report to Jenkins
                junit 'build/test_results.xml'
            }
        }
    }

    post {
        always {
            // Archiving artifacts and cleaning workspace
            archiveArtifacts artifacts: '**/build/test_results.xml', allowEmptyArchive: true
            cleanWs()
        }
    }
}
