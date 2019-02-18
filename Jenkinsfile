pipeline {
    agent any
    stages {
        stage('Test'){
            steps {
                sh 'touch text.txt'
                sh 'scp -p test.txt insights@10.180.1.12:test/'
            }
        }
    }
}
