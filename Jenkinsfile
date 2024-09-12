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
                    cmake .. -G "MinGW Makefiles" -DCOVERAGE=ON
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
                    make coveragecmake
                '''
            }
        }

        stage('Publish Test Results') {
            steps {
                // Publish the XML report to Jenkins!!
                junit 'build/test_results.xml'

                // Publish HTML report
                publishHTML ([
                    reportDir: 'build',
                    reportFiles: 'coverage_report.html',
                    reportName: 'HTML Test Report',
                    allowMissing: false,
                    alwaysLinkToLastBuild: true,
                    keepAll: true
                ])
            }
        }
    }

    post {
        always {
            // // Archiving artifacts and cleaning workspace
            // archiveArtifacts artifacts: '**/build/test_results.xml, **/build/*.html', allowEmptyArchive: true
            cleanWs()
        }
    }
}
