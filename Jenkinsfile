pipeline {
    agent any
    stages {
        stage('First') {
            steps {
                sh 'printenv'
                sh 'mkdir test'
            }
        }
        stage('Second'){
            steps {
                sh 'echo test >> test/test.txt'
                sh 'touch test/second_test.txt'
                sh 'echo "changement detecté" >> test/chg.txt'
                sh 'ls -l'
            }
        }
        stage('Final'){
            steps {
                sh 'scp -r -p test insights@10.180.1.12:test'
            }
        }
    }
}
