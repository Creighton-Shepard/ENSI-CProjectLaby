pipeline {
    agent any
    stages {
        stage('Intro'){

        }
        stage('Test'){
            sshagent (credentials: ['jenkins-server_key']){
                sh 'scp test.txt '
            }
    }
}
