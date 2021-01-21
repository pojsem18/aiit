function [qrs_signal] = ecg_qrsdetect(ecg_wave, ecg_qrs_template, threshold)
%ecg_wave: input signal
%ecg_qrs_template:   template of a qrs singal complex
%threshold: threshold factor(between 0 y 1) for detecting the qrs signal
%after cross-correlation
    global DEBUG_ECG
    
    ecg_qrs_correlation = xcorr(ecg_qrs_template-mean(ecg_qrs_template), ecg_wave-mean(ecg_wave));      % subtract mean from ecg_wave and ecg_qrs_template and make Cross-correlation
    ecg_qrs_correlation = ecg_qrs_correlation(1:round(length(ecg_qrs_correlation)/2));                         % cut first N Elements of 2N Cross-correlation
    ecg_qrs_correlation = ecg_qrs_correlation/max(ecg_qrs_correlation);                                 % normalize result of Cross-correlation
    
    qrs_signal = zeros(1, length(ecg_qrs_correlation));
    qrs_signal(find(ecg_qrs_correlation>threshold)) = 1;
    
    qrs_signal = [0, diff(qrs_signal)];
    
    ks = find(qrs_signal>0);
    kf = find(qrs_signal<0);
    
    qrs_signal = zeros(1, length(ks));
    for n=1:length(ks)
        [dummy, qrs_signal(n)] = max(ecg_qrs_correlation(ks(n):kf(n)));
        qrs_signal(n) = ks(n) + qrs_signal(n)-1;
    end

    if DEBUG_ECG
        hfig = figure('Name','Detect QRS patter with Cross-correlation','NumberTitle','off');
        subplot(3,1,1);
        plot(ecg_wave-mean(ecg_wave));
        xlabel({'Sample Number';'[-]'});
        ylabel({'U';'[mV]'});
        axis([0 16*length(ecg_qrs_template) min(ecg_wave-mean(ecg_wave)) max(ecg_wave-mean(ecg_wave))]);
        title('ecg signal');

        subplot(3,1,2);
        plot(ecg_qrs_template-mean(ecg_qrs_template));
        xlabel({'Sample Number';'[-]'});
        ylabel({'U';'[mV]'});
        axis([0 4*length(ecg_qrs_template) min(ecg_qrs_template-mean(ecg_qrs_template)) max(ecg_qrs_template-mean(ecg_qrs_template))]);
        title('qrs template');

        subplot(3,1,3);    
        plot(ecg_qrs_correlation);
        hold on;
        plot(qrs_signal, ecg_qrs_correlation(qrs_signal), '*r');
        xlabel({'Sample Number';'[-]'});
        ylabel({'U';'[mV]'});    
        axis([0 16*length(ecg_qrs_template) 0 max(ecg_qrs_correlation)]);
        title('Cross correlation of ecg signal and qrs template');
    end
end
