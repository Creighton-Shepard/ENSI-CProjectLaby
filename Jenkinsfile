pipeline {
    agent any
    stages {
        stage('Intro'){
            steps {
                sh 'echo "Test" >> test.txt'
                sh 'printenv'
            }
        }
        stage('Test'){
            steps {
                sh 'ssh -v -o StrictHostKeyChecking=no insights@10.180.1.12 uptime'
                sh 'scp docker-compose.yml insights@10.180.1.12:/home/insights/test'
                sh 'ssh -v insights@10.180.1.12 \'docker-compose -f /home/insights/test/docker-compose.yml up -d\' '
            }
        }
    }
}
