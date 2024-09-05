pipeline {
    agent any

    environment {
        BUILD_DIR = 'build'
        TEST_BINARY = 'my_test_executable.exe' // Change to your test executable name
        HTML_REPORT = 'test_results.html' // The name of the HTML report file
    }

    stages {
        stage('Clone Repository') {
            steps {
                // Clone the GitHub repository containing your code and Google Tests
                git url: 'https://github.com/username/repo.git', branch: 'main' // Change to your repository URL and branch
            }
        }

        stage('Install MinGW') {
            steps {
                // Install MinGW (if not already installed) to cross-compile for Windows
                sh '''
                    sudo apt-get update
                    sudo apt-get install -y mingw-w64
                '''
            }
        }

        stage('Build') {
            steps {
                // Build the project using MinGW to cross-compile for Windows
                sh '''
                    mkdir -p ${BUILD_DIR}
                    cd ${BUILD_DIR}
                    cmake .. -DCMAKE_TOOLCHAIN_FILE=/usr/share/mingw/toolchain-mingw32.cmake
                    make
                '''
            }
        }

        stage('Run Tests') {
            steps {
                // Run the tests and save the output as HTML (you might need Wine to run Windows executables on Linux)
                sh '''
                    cd ${BUILD_DIR}
                    wine ${TEST_BINARY} --gtest_output=html:${HTML_REPORT}
                '''
            }
        }

        stage('Publish Test Results') {
            steps {
                // Publish the HTML report to Jenkins
                publishHTML([
                    reportDir: "${BUILD_DIR}", // Directory where the report is located
                    reportFiles: "${HTML_REPORT}", // The HTML file to publish
                    reportName: "Test Results", // Name for the report in Jenkins
                    keepAll: true, // Keep all reports
                    alwaysLinkToLastBuild: true // Always link to the last build's report
                ])
            }
        }

        stage('Open HTML Report') {
            steps {
                script {
                    // Construct the URL for the HTML report in Jenkins
                    def reportUrl = "${env.JENKINS_URL}${env.JOB_NAME}/lastBuild/${BUILD_DIR}/${HTML_REPORT}"
                    echo "Report URL: ${reportUrl}" // Output the URL to console
                }
            }
        }
    }

    post {
        always {
            // Archiving artifacts and cleaning workspace
            archiveArtifacts artifacts: '**/build/*', allowEmptyArchive: true
            cleanWs()
        }
    }
}
