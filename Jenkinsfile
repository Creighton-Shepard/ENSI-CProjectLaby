pipeline {
    agent any
    stages {
        stage('Intro'){
            steps {
                sh 'echo "Test" >> test.txt'
            }
        }
        stage('Test'){
            steps {
                sh 'ssh insights@10.180.1.12 \'ls -al\''
            }
        }
    }
}
